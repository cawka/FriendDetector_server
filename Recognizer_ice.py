# **********************************************************************
#
# Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
#
# This copy of Ice is licensed to you under the terms described in the
# ICE_LICENSE file included in this distribution.
#
# **********************************************************************

# Ice version 3.3.1
# Generated from file `Recognizer.ice'

import Ice, IcePy, __builtin__

if not Ice.__dict__.has_key("_struct_marker"):
    Ice._struct_marker = object()

# Start of module FriendDetector
_M_FriendDetector = Ice.openModule('FriendDetector')
__name__ = 'FriendDetector'

if not _M_FriendDetector.__dict__.has_key('_t_File'):
    _M_FriendDetector._t_File = IcePy.defineSequence('::FriendDetector::File', (), IcePy._t_byte)

if not _M_FriendDetector.__dict__.has_key('_t_Files'):
    _M_FriendDetector._t_Files = IcePy.defineSequence('::FriendDetector::Files', (), _M_FriendDetector._t_File)

if not _M_FriendDetector.__dict__.has_key('FacePosition'):
    _M_FriendDetector.FacePosition = Ice.createTempClass()
    class FacePosition(object):
        def __init__(self, left=0, top=0, right=0, bottom=0):
            self.left = left
            self.top = top
            self.right = right
            self.bottom = bottom

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.left)
            _h = 5 * _h + __builtin__.hash(self.top)
            _h = 5 * _h + __builtin__.hash(self.right)
            _h = 5 * _h + __builtin__.hash(self.bottom)
            return _h % 0x7fffffff

        def __cmp__(self, other):
            if other == None:
                return 1
            if self.left < other.left:
                return -1
            elif self.left > other.left:
                return 1
            if self.top < other.top:
                return -1
            elif self.top > other.top:
                return 1
            if self.right < other.right:
                return -1
            elif self.right > other.right:
                return 1
            if self.bottom < other.bottom:
                return -1
            elif self.bottom > other.bottom:
                return 1
            return 0

        def __str__(self):
            return IcePy.stringify(self, _M_FriendDetector._t_FacePosition)

        __repr__ = __str__

    _M_FriendDetector._t_FacePosition = IcePy.defineStruct('::FriendDetector::FacePosition', FacePosition, (), (
        ('left', (), IcePy._t_int),
        ('top', (), IcePy._t_int),
        ('right', (), IcePy._t_int),
        ('bottom', (), IcePy._t_int)
    ))

    _M_FriendDetector.FacePosition = FacePosition
    del FacePosition

if not _M_FriendDetector.__dict__.has_key('_t_FacePositions'):
    _M_FriendDetector._t_FacePositions = IcePy.defineSequence('::FriendDetector::FacePositions', (), _M_FriendDetector._t_FacePosition)

if not _M_FriendDetector.__dict__.has_key('Face'):
    _M_FriendDetector.Face = Ice.createTempClass()
    class Face(object):
        def __init__(self, position=Ice._struct_marker, name=''):
            if position is Ice._struct_marker:
                self.position = _M_FriendDetector.FacePosition()
            else:
                self.position = position
            self.name = name

        def __hash__(self):
            _h = 0
            _h = 5 * _h + __builtin__.hash(self.position)
            _h = 5 * _h + __builtin__.hash(self.name)
            return _h % 0x7fffffff

        def __cmp__(self, other):
            if other == None:
                return 1
            if self.position < other.position:
                return -1
            elif self.position > other.position:
                return 1
            if self.name < other.name:
                return -1
            elif self.name > other.name:
                return 1
            return 0

        def __str__(self):
            return IcePy.stringify(self, _M_FriendDetector._t_Face)

        __repr__ = __str__

    _M_FriendDetector._t_Face = IcePy.defineStruct('::FriendDetector::Face', Face, (), (
        ('position', (), _M_FriendDetector._t_FacePosition),
        ('name', (), IcePy._t_string)
    ))

    _M_FriendDetector.Face = Face
    del Face

if not _M_FriendDetector.__dict__.has_key('_t_Faces'):
    _M_FriendDetector._t_Faces = IcePy.defineSequence('::FriendDetector::Faces', (), _M_FriendDetector._t_Face)

if not _M_FriendDetector.__dict__.has_key('Recognizer'):
    _M_FriendDetector.Recognizer = Ice.createTempClass()
    class Recognizer(Ice.Object):
        def __init__(self):
            if __builtin__.type(self) == _M_FriendDetector.Recognizer:
                raise RuntimeError('FriendDetector.Recognizer is an abstract class')

        def ice_ids(self, current=None):
            return ('::FriendDetector::Recognizer', '::Ice::Object')

        def ice_id(self, current=None):
            return '::FriendDetector::Recognizer'

        def ice_staticId():
            return '::FriendDetector::Recognizer'
        ice_staticId = staticmethod(ice_staticId)

        #
        # Operation signatures.
        #
        # def findFacesAndRecognizePeople(self, jpegFile, current=None):
        # def recognizePeople(self, listOfJpegFiles, current=None):
        # def learn(self, listOfFacesToLearn, current=None):

        def __str__(self):
            return IcePy.stringify(self, _M_FriendDetector._t_Recognizer)

        __repr__ = __str__

    _M_FriendDetector.RecognizerPrx = Ice.createTempClass()
    class RecognizerPrx(Ice.ObjectPrx):

        def findFacesAndRecognizePeople(self, jpegFile, _ctx=None):
            return _M_FriendDetector.Recognizer._op_findFacesAndRecognizePeople.invoke(self, ((jpegFile, ), _ctx))

        def recognizePeople(self, listOfJpegFiles, _ctx=None):
            return _M_FriendDetector.Recognizer._op_recognizePeople.invoke(self, ((listOfJpegFiles, ), _ctx))

        def learn(self, listOfFacesToLearn, _ctx=None):
            return _M_FriendDetector.Recognizer._op_learn.invoke(self, ((listOfFacesToLearn, ), _ctx))

        def checkedCast(proxy, facetOrCtx=None, _ctx=None):
            return _M_FriendDetector.RecognizerPrx.ice_checkedCast(proxy, '::FriendDetector::Recognizer', facetOrCtx, _ctx)
        checkedCast = staticmethod(checkedCast)

        def uncheckedCast(proxy, facet=None):
            return _M_FriendDetector.RecognizerPrx.ice_uncheckedCast(proxy, facet)
        uncheckedCast = staticmethod(uncheckedCast)

    _M_FriendDetector._t_RecognizerPrx = IcePy.defineProxy('::FriendDetector::Recognizer', RecognizerPrx)

    _M_FriendDetector._t_Recognizer = IcePy.defineClass('::FriendDetector::Recognizer', Recognizer, (), True, None, (), ())
    Recognizer.ice_type = _M_FriendDetector._t_Recognizer

    Recognizer._op_findFacesAndRecognizePeople = IcePy.Operation('findFacesAndRecognizePeople', Ice.OperationMode.Normal, Ice.OperationMode.Normal, False, (), (((), _M_FriendDetector._t_File),), (), _M_FriendDetector._t_Faces, ())
    Recognizer._op_recognizePeople = IcePy.Operation('recognizePeople', Ice.OperationMode.Normal, Ice.OperationMode.Normal, False, (), (((), _M_FriendDetector._t_Files),), (), _M_FriendDetector._t_Faces, ())
    Recognizer._op_learn = IcePy.Operation('learn', Ice.OperationMode.Normal, Ice.OperationMode.Normal, False, (), (((), _M_FriendDetector._t_Faces),), (), None, ())

    _M_FriendDetector.Recognizer = Recognizer
    del Recognizer

    _M_FriendDetector.RecognizerPrx = RecognizerPrx
    del RecognizerPrx

# End of module FriendDetector
