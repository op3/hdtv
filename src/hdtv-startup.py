import ROOT
from hdtv import HDTV

ROOT.TH1.AddDirectory(ROOT.kFALSE)

hdtv = HDTV()

def s_get(fname):
    hdtv.SpecGet(fname)
    
def s_getn(n, det):
    s_get("/mnt/omega/braun/88Zr_angle_singles/%04d/ge%d.%04d" % (n, det, n))
    
def s_list():
    hdtv.SpecList()
    
def s_del(sid):
	hdtv.SpecDel(sid)
    
hdtv.RegisterKeyHandler("hdtv")

### Debug ###
#s_getn(108, 0)
#hdtv.fViewport.ShowAll()
### End Debug ###

print "Welcome to HDTV"


