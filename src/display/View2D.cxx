/*
 * HDTV - A ROOT-based spectrum analysis software
 *  Copyright (C) 2006-2009  Norbert Braun <n.braun@ikp.uni-koeln.de>
 *
 * This file is part of HDTV.
 *
 * HDTV is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * HDTV is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HDTV; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 * 
 */

#include "View2D.h"
#include <X11/Xlib.h>
#include <iostream>
#include <complex>
#include <KeySymbols.h>

namespace HDTV {
namespace Display {

View2D::View2D(const TGWindow *p, UInt_t w, UInt_t h, TH2 *mat)
  : View(p, w, h)
{
  SetBackgroundColor(GetBlackPixel());
    
  fMatrix = mat;
  fMatrixMax = fMatrix->GetMaximum();
  
  fStatusBar = NULL;
  
  ZoomFull(false);
  fZVisibleRegion = Log(fMatrixMax)+1.0;
  fLogScale = true;
   
  AddInput(kKeyPressMask);
}

View2D::~View2D()
{
  FlushTiles();
}

void View2D::ShiftOffset(int dX, int dY)
{
  fXTileOffset += dX;
  fYTileOffset += dY;
  
  gClient->NeedRedraw(this);
}

/* Copied from GSViewport: Merge? */
Bool_t View2D::HandleMotion(Event_t *ev)
{
  bool cv = fCursorVisible;
  int dX = (int) fCursorX - ev->fX;
  int dY = (int) fCursorY - ev->fY;
  if(cv) DrawCursor();
  
  fCursorX = ev->fX;
  fCursorY = ev->fY;
  
  if(fDragging) {
	ShiftOffset(-dX, -dY);
  }
    
  if(cv) DrawCursor();
  
  UpdateStatusBar();
  
  return true;
}

Bool_t View2D::HandleButton(Event_t *ev)
{
  if(ev->fType == kButtonPress)
	fDragging = true;
  else
	fDragging = false;
	
  return true;
}

Bool_t View2D::HandleKey(Event_t *ev)
{
  UInt_t keysym;
  char buf[16];
    
  if(ev->fType == kGKeyPress) {
	gVirtualX->LookupString(ev, buf, 16, keysym);
    switch(keysym) {
	  case kKey_w:
	    fZVisibleRegion *= 2;
	    Update();
	    break;
	  case kKey_s:
	    fZVisibleRegion /= 2;
	    Update();
	    break;
	  case kKey_z:
	    ZoomAroundCursor(2.0);
	    break;
	  case kKey_x:
		ZoomAroundCursor(0.5);
	    break;
	  case kKey_1:
	    ZoomAroundCursor(1.0 / fXZoom);
	    break;
	  case kKey_f:
	    ZoomFull();
	    break;
	  case kKey_l:
	    fLogScale = !fLogScale;
	    if(fLogScale)
	      fZVisibleRegion = Log(fMatrixMax);
	    else
	      fZVisibleRegion = fMatrixMax;
	    Update();
	}
  }
	
  return true;
}

void View2D::Update()
{
  FlushTiles();
  gClient->NeedRedraw(this);
  UpdateStatusBar();
}

void View2D::ZoomAroundCursor(double f, Bool_t update)
{
  fXTileOffset = (int)((1.0 - f) * (double) fCursorX + (double) fXTileOffset * f);
  fYTileOffset = (int)((1.0 - f) * (double) fCursorY + (double) fYTileOffset * f);

  fXZoom *= f;
  fYZoom *= f;
  
  if(update)
    Update();
}

void View2D::ZoomFull(Bool_t update)
{
  fXZoom = (double) fWidth / fMatrix->GetNbinsX();
  fYZoom = (double) fHeight / fMatrix->GetNbinsY();
  
  if(fXZoom > fYZoom)
    fXZoom = fYZoom;
  else
    fYZoom = fXZoom;
    
  fXTileOffset = 0;
  fYTileOffset = fHeight;
    
  if(update)
    Update();
}

double View2D::Log(double x)
{
  if(x < 0.0)
    return 0.0;
  else if(x < 1.0)
    return x;
  else
    return log(x) + 1.0;
}

Bool_t View2D::HandleCrossing(Event_t *ev)
{
  if(ev->fType == kEnterNotify) {
	if(fCursorVisible) DrawCursor();
	fCursorX = ev->fX;
	fCursorY = ev->fY;
	DrawCursor();
  } else if(ev->fType == kLeaveNotify) {
	if(fCursorVisible) DrawCursor();
  }
  
  return true;
}

void View2D::UpdateStatusBar()
{
  char tmp[32];
  if(fStatusBar) {
    snprintf(tmp, 32, "%.1f %.1f", (double) XScrToCh(fCursorX) / 2.0,
                                   (double) YScrToCh(fCursorY) / 2.0);
    fStatusBar->SetText(tmp);
  }
}

void View2D::ZtoRGB(int z, int &r, int &g, int &b)
{
  if(z < 0) {
    r = 0;
    g = 0;
    b = 0;
  } else if(z < 256) {
    r = 0;
    g = 0;
    b = z;
  } else if(z < 2 * 256) {
    r = 0;
	g = z - 256;
	b = 255;
  } else if(z < 3 * 256) {
    r = 0;
    g = 255;
    b = 3 * 256 - z - 1;
  } else if(z < 4 * 256) {
    r = z - 3 * 256;
    g = 255;
    b = 0;
  } else if(z < 5 * 256) {
    r = 255;
    g = 5 * 256 - z - 1;
    b = 0;
  } else {
    r = 255;
    g = 0;
    b = 0;
  }
}

int View2D::GetValueAtPixel(int x, int y)
{
  double z;
 
  if(x < 0 || y < 0)
    return ZCtsToScr(0);

  z = fMatrix->GetBinContent(XTileToCh(x), YTileToCh(y));
  
  if(fLogScale)
    z = Log(z);
  
  return ZCtsToScr(z);
}

Pixmap_t View2D::RenderTile(int xoff, int yoff)
{
  int x, y, z;
  int r, g, b;
  Pixmap_t pixmap;
  Drawable_t img;
  ULong_t pixel;
  unsigned long r_mask, g_mask, b_mask;
  int r_shift, g_shift, b_shift;

  img = gVirtualX->CreateImage(cTileSize, cTileSize);
  
  /* Calculate shifts required for color channels. Positive shifts go to the left,
     negative shifts go to the right.
     
     NOTE: This code only works as long as the bit mask for each color channel
     contains only a single, continuous strings of 1s. Otherwise, much more
     complicated and slow code would be needed, as a single shift would no
     longer be sufficient.   */
  r_mask = ((XImage*)img)->red_mask;
  g_mask = ((XImage*)img)->green_mask;
  b_mask = ((XImage*)img)->blue_mask;
  
  r_shift = g_shift = b_shift = 0;
  while(r_mask) { r_mask >>= 1; r_shift++; }  r_shift -= 8;
  while(g_mask) { g_mask >>= 1; g_shift++; }  g_shift -= 8;
  while(b_mask) { b_mask >>= 1; b_shift++; }  b_shift -= 8;
  
  r_mask = ((XImage*)img)->red_mask;
  g_mask = ((XImage*)img)->green_mask;
  b_mask = ((XImage*)img)->blue_mask;
  
  for(y=0; y<cTileSize; y++) {
    for(x=0; x<cTileSize; x++) {
      z = GetValueAtPixel(x + xoff*cTileSize, -(y + yoff*cTileSize));
      ZtoRGB(z, r, g, b);
      
      r = (r_shift > 0) ? (r << r_shift) : (r >> (-r_shift));
      g = (g_shift > 0) ? (g << g_shift) : (g >> (-g_shift));
      b = (b_shift > 0) ? (b << b_shift) : (b >> (-b_shift));
      pixel = (r & r_mask) | (g & g_mask) | (b & b_mask);
      gVirtualX->PutPixel(img, x, y, pixel);
    }
  }
  
  pixmap = gVirtualX->CreatePixmap(GetId(), cTileSize, cTileSize);
  gVirtualX->PutImage(pixmap, GetWhiteGC()(), img,
            0, 0, 0, 0, cTileSize, cTileSize);
  gVirtualX->DeleteImage(img);
  
  return pixmap;
}

void View2D::WeedTiles()
{
  int16_t x, y;
  int xpos, ypos;
  std::map<uint32_t,Pixmap_t>::iterator iter, elem;
  
  iter = fTiles.begin();
  while(iter != fTiles.end()) {
    elem = iter;
    iter++;
    x = elem->first & 0xFFFF;
    y = elem->first >> 16;
    xpos = (int) x*cTileSize+fXTileOffset;
    ypos = (int) y*cTileSize+fYTileOffset;
    
    if(xpos < -2 * cTileSize || xpos > (int) fWidth + cTileSize ||
       ypos < -2 * cTileSize || ypos > (int) fHeight + cTileSize) {
      //cout << "Deleting Tile " << x << " " << y << " " << xpos << " " << ypos << endl;
      gVirtualX->DeletePixmap(elem->second);
      fTiles.erase(elem);  
    }
  }
}

void View2D::FlushTiles()
{
  std::map<uint32_t,Pixmap_t>::iterator iter;
  
  for(iter = fTiles.begin(); iter != fTiles.end(); iter++) {
    gVirtualX->DeletePixmap(iter->second);
  }
  fTiles.clear();
}

Pixmap_t View2D::GetTile(int x, int y)
{
  uint32_t id = y << 16 | x & 0xFFFF;
  std::map<uint32_t, Pixmap_t>::iterator iter;
  
  iter = fTiles.find(id);
  if(iter == fTiles.end()) {
    Pixmap_t tile = RenderTile(x, y);
    //cout << "Rendering Tile " << x << " " << y << endl;
    fTiles.insert(std::make_pair(id, tile));
    return tile;
  } else {
    return iter->second;
  }
}

void View2D::DoRedraw()
{
  int x, y;
  int x1, y1, x2, y2;
  bool cv = fCursorVisible;
  Pixmap_t tile;
  unsigned int NTiles;
  
  x1 = GetTileId(-fXTileOffset);
  x2 = GetTileId(fWidth - fXTileOffset);
  y1 = GetTileId(-fYTileOffset);
  y2 = GetTileId(fHeight - fYTileOffset);
  
  if(cv) DrawCursor();
  
  for(x=x1; x<=x2; x++) {
    for(y=y1; y<=y2; y++) {
      tile = GetTile(x,y);
      gVirtualX->CopyArea(tile, GetId(), GetWhiteGC()(), 
        0, 0, cTileSize, cTileSize, x*cTileSize+fXTileOffset, y*cTileSize+fYTileOffset);
    }
  }
  
  if(cv) DrawCursor();
  
  NTiles = (fWidth/cTileSize + 4) * (fHeight/cTileSize + 4);
  if(fTiles.size() > NTiles) {
    //cout << "Weeding..." << endl;
    WeedTiles();
  }
}

} // end namespace Display
} // end namespace HDTV