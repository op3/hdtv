# -*- coding: utf-8 -*-

# HDTV - A ROOT-based spectrum analysis software
#  Copyright (C) 2006-2009  The HDTV development team (see file AUTHORS)
#
# This file is part of HDTV.
#
# HDTV is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 2 of the License, or (at your
# option) any later version.
#
# HDTV is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License
# along with HDTV; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
import ROOT
import copy

import hdtv.cal
import hdtv.color

from hdtv.drawable import Drawable
from hdtv.util import Position


class Marker(Drawable):
    """ 
    Markers in X or in Y direction
    
    Every marker contains a pair of positions as many markers come always in 
    pairs to mark a region (like background markers). Of course it is also 
    possible to have markers that consist of a single marker, then the second 
    position is None.
    """
    def __init__(self, xytype, p1, color=hdtv.color.zoom, cal=None, connecttop=False):
        self._activeColor = color
        self._cal = cal
        self.fixedInCal = True
        self.xytype = xytype
        self.connecttop = connecttop
        self.p1 = p1
        self.p2 = None
        Drawable.__init__(self, color=color, cal=cal)
    
    # color property
    def _set_color(self, color):
        # active color is given at creation and should not change
        self._passiveColor = hdtv.color.Highlight(color, active=False)
        if self.displayObj:
            if self.active:
                self.displayObj.SetColor(self._activeColor)
            else:
                self.displayObj.SetColor(self._passiveColor)
            
    def _get_color(self):
        return self._passiveColor
        
    color = property(_get_color, _set_color)
     
    # p1 property
    def _set_p1(self, pos):
        if isinstance(pos, (float,int)):
            pos = hdtv.util.Position(pos, self.fixedInCal, self.cal)
        self._p1 = pos
  
    def _get_p1(self):
        return self._p1
        
    p1 = property(_get_p1, _set_p1)
    
    # p2 property
    def _set_p2(self, pos):
        if isinstance(pos, (float,int)):
            pos = hdtv.util.Position(pos, self.fixedInCal, self.cal)
        self._p2 = pos
        
    def _get_p2(self):
        return self._p2

    p2 = property(_get_p2, _set_p2)
    
    #cal property
    def _set_cal(self, cal):
        self.p1.cal = cal
        if self.p2 is not None:
            self.p2.cal = cal
        Drawable._set_cal(self, cal)
        
    def _get_cal(self):
        return self._cal
    
    cal = property(_get_cal, _set_cal)
        
    
    def Draw(self, viewport):
        """ 
        Draw the marker
        """
        if self.viewport and not self.viewport == viewport:
            # Marker can only be drawn to a single viewport
            raise RuntimeError, "Marker cannot be realized on multiple viewports"
        self.viewport = viewport
        # adjust the position values for the creation of the makers
        # on the C++ side all values must be uncalibrated
        p1 = self.p1.pos_uncal
        if self.p2 == None:
            n = 1
            p2 = 0.0
        else:
            n = 2
            p2 = self.p2.pos_uncal
        # X or Y?
        if self.xytype == "X":
            constructor = ROOT.HDTV.Display.XMarker
        elif self.xytype == "Y":
            constructor = ROOT.HDTV.Display.YMarker
        if self.active:
            self.displayObj = constructor(n, p1, p2, self._activeColor)
        else:
            self.displayObj = constructor(n, p1, p2, self._passiveColor)
        if self.xytype=="X":
            # these properties make only sense on the X axis
            self.displayObj.SetConnectTop(self.connecttop)
            if self.cal:
                self.displayObj.SetCal(self.cal)
            if self.ID is not None:
                self.displayObj.SetID(self.ID)
        self.displayObj.Draw(self.viewport)

        
    def Refresh(self):
        p1 = self.p1.pos_uncal
        if self.p2 is None:
            # on the C++ side all values must be uncalibrated
            self.displayObj.SetN(1)
            self.displayObj.SetPos(p1)
        else:
            # on the C++ side all values must be uncalibrated
            p2 = self.p2.pos_uncal
            self.displayObj.SetN(2)
            self.displayObj.SetPos(p1, p2)
  
    def __str__(self):
        if not self.p2 is None:
            return '%s marker at %s and %s' %(self.xytype, self.p1, self.p2)
        else:
            return '%s marker at %s' %(self.xytype, self.p1)

    def __copy__(self):
        """
        Create a copy of this marker
        """
        p1 = copy.copy(self.p1)
        new = Marker(self.xytype, p1, self._activeColor, self.cal)

        if self.p2 is not None:
            new.p2 = copy.copy(self.p2)
        return new

    def FixCal(self):
        self.fixedInCal = True
        self.p1.FixCal()
        if self.p2 is not None:
            self.p2.FixCal()
        
    def FixUncal(self):
        self.fixedInCal = False
        self.p1.FixUncal()
        if self.p2 is not None:
            self.p2.FixUncal()
            

class MarkerCollection(list):
    """
    A collection of identical markers
    """
    def __init__(self, xytype, paired=False, maxnum=None, color=None, cal=None, connecttop=True):
        list.__init__(self)
        self.viewport = None
        self.xytype = xytype
        self.paired = paired
        self.maxnum = maxnum
        self.connecttop = connecttop
        self.cal = cal
        self.ID = None
        # active color is defined at creation time of MarkerCollection
        self.activeColor = color
        # color = passiveColor can be changed
        self.color = hdtv.color.Highlight(color, active=False)
        self.active = True     # By default markers are active when newly created
        self.fixedInCal = True # By default markers are fixed in calibrated space
        
    # delegate everthing to the markers
    def __setattr__(self, name, value):
        for marker in self:
            if hasattr(marker, name):
                marker.__setattr__(name, value)
        self.__dict__[name] = value
        
    def setProperties(self, marker):
        marker.connecttop = self.connecttop
        marker.activeColor = self.activeColor
        marker.color = self.color
        marker.cal = self.cal
        marker.ID = self.ID
        marker.active = self.active
        marker.fixedInCal = self.fixedInCal
        
    def append(self, marker):
        self.setProperties(marker)
        list.append(self, marker)
        
    def Draw(self, viewport):
        self.viewport = viewport
        for marker in self:
            marker.Draw(self.viewport)

    def Show(self):
        for marker in self:
            marker.Show()

    def Hide(self):
        for marker in self:
            marker.Hide()
        
    def Refresh(self):
        for marker in self:
            marker.Refresh()

    def FixCal(self):
        self.fixedInCal = True
        for marker in self:
            marker.FixCal()
    
    def FixUncal(self):
        self.fixedInCal = False
        for marker in self:
            marker.FixUncal()
            
            
    def SetMarker(self, pos):
        """
        Set a marker to calibrated position pos, possibly completing a marker pair
        """
        if self.IsFull():
            pending = self.pop(0)
            pending.p1 = pos
            pending.p2 = None
            pending.Refresh()
            self.append(pending)
        elif self.IsPending():
            pending = self[-1]
            pending.p2 = pos
            pending.Refresh()
        else:
            m = Marker(self.xytype, pos, self.activeColor, self.cal, self.connecttop)
            m.color = self.color
            m.ID = self.ID
            m.active = self.active
            self.append(m)
            if self.viewport:
                m.Draw(self.viewport)
                
    def IsFull(self):
        """
        Checks if this MarkerCollection already contains the maximum number of
        markers allowed
        """
        if self.maxnum == None:
            return False
        if self.IsPending():
            return False
        return len(self) == self.maxnum
        
        
    def IsPending(self):
        """
        Checks if there is a single marker waiting to form a pair.
        Always returns False if this is a MarkerCollection with paired == False.
        """
        if not self.paired:
            return False
        return (len(self) > 0 and self[-1].p2 == None)
    
    
    def Clear(self):
        """
        Remove all markers from this collection
        """
        if self.viewport != None:
            self.viewport.LockUpdate()
        while self:
            self.pop()
        if self.viewport != None:
            self.viewport.UnlockUpdate()
        
        
    def RemoveNearest(self, pos):
        """
        Remove the marker that is nearest to pos
        If one of the members of a marker pair is nearest to pos, 
        both are removed
        """
        if len(self)==0:
            hdtv.ui.warn("No marker available, no action taken")
            return
        index = dict()
        for m in self:
            p1 = m.p1.pos_cal
            diff = abs(pos-p1)
            index[diff] = m
            if self.paired and not m.p2==None:
                p2 = m.p2.pos_cal
                diff = abs(pos-p2)
                index[diff] = m
        nearest = index[min(index.keys())]
        self.remove(nearest)
        self.Refresh()
        
    

