import ROOT
import os
import UserDict

import hdtv.dlmgr

hdtv.dlmgr.LoadLibrary("display")

class Drawable:
	def __init__(self, color=None):
		self.viewport = None
		self.displayObj = None
		self.color = color

	def __str__(self):
		return 'drawable object'

	def Draw(self, viewport):
		"""
		This function must create the appropriate object from the underlying
		C++ display code and call its draw function.
		Attention: Unlike the Display object of the underlying implementation,
		python objects can only be drawn on a single viewport
		"""
		pass
		
	def Refresh(self):
		"""
		Refresh the objects data (e.g. reload a Spectrum from disk)
		"""
		pass

	def Remove(self):
		"""
		Remove the object 
		"""
		if not self.viewport:
			return
		self.displayObj.Remove()
		self.displayObj = None
		# finally remove the viewport from this object
		self.viewport = None

	def Show(self):
		"""
		Show the object 
		"""
		self.displayObj.Show()

	def Hide(self):
		"""
		Hide the object 
		"""
		self.displayObj.Hide()

	def SetColor(self, color):
		"""
		set color of the object 
		"""
		if color:
			self.color = color
		# update the display if needed	
		if self.displayObj != None:
			try:
				self.displayObj.SetColor(color)
			except:
				# FIXME: should not happen!
				print 'SetColor failed for %s' % self.displayObj
		
	def ToTop(self):
		"""
		Move the spectrum to the top of its draw stack
		"""
		if self.displayObj:
			try:
				self.displayObj.ToTop()
			except: # does not matter
				pass
			

	def ToBottom(self):
		"""
		Move the spectrum to the top of its draw stack
		"""
		if self.displayObj:
			try:
				self.displayObj.ToBottom()
			except: # does not matter
				pass


class DrawableCompound(UserDict.DictMixin):
	"""
	"""
	def __init__(self, viewport):
		self.viewport = viewport
		self.objects = dict()
		self.visible = set()
		self.activeID = None

	def __getitem__(self, ID):
		return self.objects.__getitem__(ID)

	def __setitem__(self, ID, obj):
		self.objects.__setitem__(ID, obj)
		obj.Draw(self.viewport)
		self.visible.add(ID)

	def __delitem__(self, ID):
		self.objects[ID].Remove()
		if ID in self.visible:
			self.visible.discard(ID)
		if ID == self.activeID:
			self.activeID = None
		self.objects.__delitem__(ID)

	def keys(self):
		return self.objects.keys()

	def Add(self, obj):
		"""
		Adds an object to the first free index in the managers dict.
		"""
		ID = self.GetFreeID()
		self.objects[ID] = obj
		return ID

	def GetFreeID(self):
		"""
		Finds the first free index in the managers dict
		"""
		# Find a free ID
		ID = 0
		while ID in self.keys():
			ID += 1
		return ID
		
	def ListObjects(self, args=None):
		"""
		List all objects in a human readable way
		"""
		for (ID, obj) in self.objects.iteritems():
			stat = " "
			if ID == self.activeID:
				stat += "A"
			else:
				stat += " "
			if ID in self.visible:
				stat += "V"
			else:
				stat += " "
			print "%d %s %s" % (ID, stat, obj)
			

	def ActivateObject(self, ID):
		"""
		Activates the object with id ID, while also highlighting it
		"""
		if not ID in self.keys():
			raise KeyError
		self.viewport.LockUpdate()
		if self.activeID != None:
			c = hdtv.color.ColorForID(self.activeID, 1., .5)
			self.objects[self.activeID].SetColor(c)
		self.objects[ID].SetColor(hdtv.color.ColorForID(ID, 1., 1.))
		self.objects[ID].ToTop()
		self.activeID = ID
		self.viewport.UnlockUpdate()
	
		
	def Draw(self, viewport):
		"""
		Draw function
		"""
		if not self.viewport == viewport:
			# Unlike the Display object of the underlying implementation,
			# python objects can only be drawn on a single viewport
			raise RuntimeError, "Object can only be drawn on a single viewport"
		self.viewport = viewport
		self.viewport.LockUpdate()
		for ID in self.iterkeys():
			self.objects[ID].Draw()
			self.visible.add(ID)
		self.viewport.UnlockUpdate()
	
	
	def Remove(self):
		"""
		Remove all objects
		"""
		self.viewport.LockUpdate()
		for ID in self.iterkeys():
			self.__delitem__(ID)
		self.viewport.UnlockUpdate()
	
	def RemoveAll(self):
		"""
		Remove all - just a wrapper for convenience
		"""
		self.Remove()

	def RemoveObjects(self, ids):
		"""
		Remove objects with the specified ids
		"""
		self.viewport.LockUpdate()
		if isinstance(ids, int):
			ids = [ids]
		for ID in ids:
			try:
				self.__delitem__(ID)
			except KeyError:
				print "Warning: ID %d not found" % ID
		self.viewport.UnlockUpdate()


	def Refresh(self):
		"""
		Refresh all objects
		"""
		self.viewport.LockUpdate()
		for obj in self.itervalues():
			obj.Refresh()
		self.viewport.UnlockUpdate()
	
	def RefreshAll(self):
		"""
		Refresh all - just a wrapper for convenience
		"""
		self.Refresh()
	
	def RefreshObjects(self, ids):
		"""
		Refresh objects with ids
		"""
		self.viewport.LockUpdate()
		if isinstance(ids, int):
			ids = [ids]
		for ID in ids:
			try:
				self.objects[ID].Refresh
			except KeyError:
				print "Warning: ID %d not found" % ID
		self.viewport.UnlockUpdate()
	
	def RefreshVisible(self):
		"""
		Refresh visible objects
		"""
		self.RefreshObjects(self.visible)
	
	
	def Hide(self):
		"""
		Hide the whole object
		"""
		self.HideAll()
			
	def HideAll(self):
		"""
		Hide all 
		"""
		self.viewport.LockUpdate()
		for ID in self.iterkeys():
			if ID in self.visible:
				self.objects[ID].Hide()
		self.visible.clear()
		self.viewport.UnlockUpdate()
			
	def HideObjects(self, ids):
		"""
		Hide objects from the display
		"""
		self.viewport.LockUpdate()
		# if only one object is given
		if isinstance(ids, int):
			ids = [ids]
		for ID in ids:
			if ID in self.visible:
				try:
					self.objects[ID].Hide()
					self.visible.discard(ID)
				except KeyError:
					print "Warning: ID %d not found" % ID
		self.viewport.UnlockUpdate()


	def Show(self):
		"""
		Show the whole object
		"""
		self.ShowAll()
		
	def ShowAll(self):
		"""
		Show all 
		"""
		self.viewport.LockUpdate()
		for ID in self.iterkeys():
			if ID not in self.visible:
				self.objects[ID].Show()
		self.visible=set(self.keys())
		self.viewport.UnlockUpdate()

	def ShowObjects(self, ids, clear=True):
		"""
		Show objects on the display. 

		If the clear parameter is True, the display is cleared first. 
		Otherwise the objects are shown in addition to the ones, that 
		are already visible.
		"""
		self.viewport.LockUpdate()
		if isinstance(ids, int):
			ids = [ids]
		if clear:
			self.HideAll()
		for ID in ids:
			if ID not in self.visible:
				try:
					self.objects[ID].Show()
					self.visible.add(ID)
				except KeyError:
					print "Warning: ID %s not found" % ID
		self.viewport.UnlockUpdate()

	def ShowNext(self, nb=1):
		"""
		Show next object (by index)

		With the parameter nb, the user can choose how many new spectra
		there should be displayed.
		"""
		if nb > len(self.objects):
			self.ShowAll()
			return
		if len(self.visible)==0 or len(self.visible)==len(self.objects):
			self.ShowFirst(nb)
			return
		ids = self.keys()
		ids.sort()
		index = ids.index(max(self.visible))
		ids = ids[index+1:index+nb+1]
		if len(ids)==0:
			self.ShowFirst(nb)
			return
		self.ShowObjects(ids, clear=True)

	def ShowPrev(self, nb=1):
		"""
		Show previous object (by index)

		With the parameter nb, the user can choose how many new spectra
		there should be displayed.
		"""
		if nb > len(self.objects):
			self.ShowAll()
			return
		if len(self.visible)==0 or len(self.visible)==len(self.objects):
			self.ShowLast(nb)
			return
		ids = self.keys()
		ids.sort()
		index = ids.index(min(self.visible))
		if nb > index:
			ids = ids[0:index]
		else:
			ids = ids[index-nb:index]
		if len(ids)==0:
			self.ShowLast(nb)
			return
		self.ShowObjects(ids, clear=True)

	def ShowFirst(self, nb=1):
		"""
		Show the first nb objects
		"""
		if nb > len(self.objects):
			self.ShowAll()
			return
		ids = self.keys()
		ids.sort()
		ids = ids[:nb]
		self.ShowObjects(ids, clear=True)

	def ShowLast(self, nb=1):
		"""
		Show the last nb objects
		"""
		if nb > len(self.objects):
			self.ShowAll()
			return
		ids = self.keys()
		ids.sort()
		ids = ids[len(ids)-nb:]
		self.ShowObjects(ids, clear=True)
		
	def SetColor(self, color):
		"""
		Set color of all objects to the same color,
		no idea if this is useful ... ?
		"""
		self.viewport.LockUpdate()
		for obj in self.itervalues():
			obj.SetColor(color)
		self.viewport.UnlockUpdate()
			