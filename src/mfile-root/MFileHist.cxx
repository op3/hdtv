#include <TArrayD.h>
#include <iostream>
#include "MFileHist.h"

const int MFileHist::ERR_SUCCESS = 0;
const int MFileHist::ERR_READ_OPEN = 1;
const int MFileHist::ERR_READ_INFO = 2;
const int MFileHist::ERR_READ_NOTOPEN = 3;
const int MFileHist::ERR_READ_BADIDX = 4;
const int MFileHist::ERR_READ_GET = 5;
const int MFileHist::ERR_READ_CLOSE = 6;
const int MFileHist::ERR_WRITE_OPEN = 7;
const int MFileHist::ERR_WRITE_INFO = 8;
const int MFileHist::ERR_WRITE_PUT = 9;
const int MFileHist::ERR_WRITE_CLOSE = 10;
const int MFileHist::ERR_INVALID_FORMAT = 11;
const int MFileHist::ERR_UNKNOWN = 12;

const char *MFileHist::GetErrorMsg(int errno)
{
	static const char *errorDesc[] = {
	  "No error",
	  "Failed to open file for reading",
	  "Failed to get info from file",
	  "File is not open",
	  "Bad index (level/line)",
	  "Failed to get data from file",
	  "Failed to close file after reading",
	  "Failed to open file for writing",
	  "Failed to put info into file",
	  "Failed to put data into file",
	  "Failed to close file after writing",
	  "Invalid format specified",
	  "Unknown error"
	};
	
	if(errno < 0 || errno > ERR_UNKNOWN)
		errno = ERR_UNKNOWN;
	
	return errorDesc[errno];
}

MFileHist::MFileHist()
{
	fHist = NULL;
	fInfo = NULL;
	fErrno = ERR_SUCCESS;
}

MFileHist::~MFileHist()
{
	delete fInfo;
	
	if(fHist)
		mclose(fHist);
}

int MFileHist::WriteTH1(const TH1 *hist, char *fname, char *fmt)
{
	MFILE *mf;
	minfo info;
	int nbins = hist->GetNbinsX();

	mf = mopen(fname, "w");
	if(!mf)
		return ERR_WRITE_OPEN;
		
	if(msetfmt(mf, fmt) != 0) {
		mclose(mf);
		return ERR_INVALID_FORMAT;
	}
	
	mgetinfo(mf, &info);
	info.levels = 1;
	info.lines = 1;
	info.columns = nbins;
	if(msetinfo(mf, &info) != 0) {
		mclose(mf);
		return ERR_WRITE_INFO;
	}
	
	TArrayD buf(nbins);
	for(int i=0; i<nbins; i++)
		buf[i] = hist->GetBinContent(i+1);
		
	if(mputdbl(mf, buf.GetArray(), 0, 0, 0, nbins) != nbins) {
		mclose(mf);
		return ERR_WRITE_PUT;
	}
	
	if(mclose(mf) != 0)
		return ERR_WRITE_CLOSE;
	
	return ERR_SUCCESS;
}

int MFileHist::WriteTH2(const TH2 *hist, char *fname, char *fmt)
{
	MFILE *mf;
	minfo info;
	int nbinsx = hist->GetNbinsX();
	int nbinsy = hist->GetNbinsY();
	int col, line;

	mf = mopen(fname, "w");
	if(!mf)
		return ERR_WRITE_OPEN;
		
	if(msetfmt(mf, fmt) != 0) {
		mclose(mf);
		return ERR_INVALID_FORMAT;
	}
	
	mgetinfo(mf, &info);
	info.levels = 1;
	info.lines = nbinsy;
	info.columns = nbinsx;
	if(msetinfo(mf, &info) != 0) {
		mclose(mf);
		return ERR_WRITE_INFO;
	}
	
	TArrayD buf(nbinsx);
	
	for(line=0; line < nbinsy; line++) {
		for(col=0; col < nbinsx; col++)
			buf[col] = hist->GetBinContent(col+1, line+1);
		
		if(mputdbl(mf, buf.GetArray(), 0, line, 0, nbinsx) != nbinsx)
			break;
	}
	
	if(line != nbinsy) {
		mclose(mf);
		return ERR_WRITE_PUT;
	}
	
	if(mclose(mf) != 0)
		return ERR_WRITE_CLOSE;
	
	return ERR_SUCCESS;
}

int MFileHist::Open(char *fname, char *fmt)
{
	/* If a format is specified, we first test if the specification is valid,
	   and return an error otherwise. We then set the format for the real matrix
	   with no further error checking. This mirrors how it is done in the matconv
	   program. */
	if(fmt && msetfmt(NULL, fmt) != 0) {
		fErrno = ERR_INVALID_FORMAT;
		return fErrno;
	}

    fHist = mopen(fname, "r");
    if(!fHist) {
    	fErrno = ERR_READ_OPEN;
    	return fErrno;
    }
    	
	if(fmt)
	    msetfmt(fHist, fmt);

	fInfo = new minfo;

    if( mgetinfo(fHist, fInfo) != 0 ) {
		delete fInfo;
		fInfo = NULL;
		
		mclose(fHist);
		fHist = NULL;
		
		fErrno = ERR_READ_INFO;
        return fErrno;
    }
    
    fErrno = ERR_SUCCESS;
    return fErrno;
}

int MFileHist::Close()
{
	delete fInfo;
	fInfo = NULL;
	fErrno = ERR_SUCCESS;
	
	if(fHist && mclose(fHist) != 0)
		fErrno = ERR_READ_CLOSE;
	fHist = NULL;
	
	return fErrno;
}

template <class histType>
histType *MFileHist::ToTH1(const char *name, const char *title, int level, int line)
{
	histType *hist;

	if(!fHist || !fInfo) {
		fErrno = ERR_READ_NOTOPEN;
		return NULL;
	}
	
	if(level >= fInfo->levels || line >= fInfo->lines) {
		fErrno = ERR_READ_BADIDX;
		return NULL;
	}
		
	hist = new histType(name, title, fInfo->columns, -0.5, (double) fInfo->columns - 0.5);
	
	// FillTH1 will set fErrno
	if(!FillTH1(hist, level, line)) {
		delete hist;
		return NULL;
	}
	
	return hist;
}

TH1 *MFileHist::FillTH1(TH1 *hist, int level, int line)
{
	if(!fHist || !fInfo) {
		fErrno = ERR_READ_NOTOPEN;
		return NULL;
	}
	
	if(level >= fInfo->levels || line >= fInfo->lines) {
		fErrno = ERR_READ_BADIDX;
		return NULL;
	}
		
	TArrayD buf(fInfo->columns);

    if(mgetdbl(fHist, buf.GetArray(), level, line, 0, fInfo->columns) != fInfo->columns) {
    	fErrno = ERR_READ_GET;
    	return NULL;
    }
    
	for(int i=0; i < fInfo->columns; i++) {
		hist->SetBinContent(i+1, buf[i]);
	}
	
	fErrno = ERR_SUCCESS;
	return hist;
}

TH1D *MFileHist::ToTH1D(const char *name, const char *title, int level, int line)
{
	return ToTH1<TH1D>(name, title, level, line);
}

TH1I *MFileHist::ToTH1I(const char *name, const char *title, int level, int line)
{
	return ToTH1<TH1I>(name, title, level, line);
}

double *MFileHist::FillBuf1D(double *buf, int level, int line)
{
	if(!fHist || !fInfo) {
		fErrno = ERR_READ_NOTOPEN;
		return NULL;
	}
	
	if(level >= fInfo->levels || line >= fInfo->lines) {
		fErrno = ERR_READ_BADIDX;
		return NULL;
	}
		
	if(mgetdbl(fHist, buf, level, line, 0, fInfo->columns) != fInfo->columns) {
		fErrno = ERR_READ_GET;
       	return NULL;
	}
    
    fErrno = ERR_SUCCESS;
    return buf;
}

TH2 *MFileHist::FillTH2(TH2 *hist, int level)
{
	int line, col;

	if(!fHist || !fInfo) {
		fErrno = ERR_READ_NOTOPEN;
		return NULL;
	}
	
	if(level >= fInfo->levels) {
		fErrno = ERR_READ_BADIDX;
		return NULL;
	}
		
	TArrayD buf(fInfo->columns);

	for(line=0; line < fInfo->lines; line++) {
	    if(mgetdbl(fHist, buf.GetArray(), level, line, 0, fInfo->columns) != fInfo->columns)
			break;
    
		for(col=0; col < fInfo->columns; col++) {
			hist->SetBinContent(col+1, line+1, buf[col]);
		}
	}
	
	if(line != fInfo->lines) {
		fErrno = ERR_READ_GET;
		return NULL;
	}
	
	fErrno = ERR_SUCCESS;
	return hist;
}

template <class histType>
histType *MFileHist::ToTH2(const char *name, const char *title, int level)
{
	histType *hist;

	if(!fHist || !fInfo) {
		fErrno = ERR_READ_NOTOPEN;
		return NULL;
	}
	
	if(level >= fInfo->levels) {
		fErrno = ERR_READ_BADIDX;
		return NULL;
	}
		
	hist = new histType(name, title,
						fInfo->columns, -0.5, (double) fInfo->columns - 0.5,
						fInfo->lines, -0.5, (double) fInfo->lines - 0.5);
	
	// FillTH2 will set fErrno
	if(!FillTH2(hist, level)) {
		delete hist;
		return NULL;
	}
	
	return hist;
}

TH2D *MFileHist::ToTH2D(const char *name, const char *title, int level)
{
	return ToTH2<TH2D>(name, title, level);
}

TH2I *MFileHist::ToTH2I(const char *name, const char *title, int level)
{
	return ToTH2<TH2I>(name, title, level);
}
