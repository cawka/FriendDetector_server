// **********************************************************************
//
// Copyright (c) 2003-2009 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.3.1
// Generated from file `Recognizer.ice'

#ifndef __Recognizer_h__
#define __Recognizer_h__

#include <Ice/LocalObjectF.h>
#include <Ice/ProxyF.h>
#include <Ice/ObjectF.h>
#include <Ice/Exception.h>
#include <Ice/LocalObject.h>
#include <Ice/Proxy.h>
#include <Ice/Object.h>
#include <Ice/Outgoing.h>
#include <Ice/Incoming.h>
#include <Ice/Direct.h>
#include <Ice/StreamF.h>
#include <Ice/UndefSysMacros.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 303
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace IceProxy
{

namespace FriendDetector
{

class Recognizer;

}

}

namespace FriendDetector
{

class Recognizer;
bool operator==(const Recognizer&, const Recognizer&);
bool operator<(const Recognizer&, const Recognizer&);

}

namespace IceInternal
{

::Ice::Object* upCast(::FriendDetector::Recognizer*);
::IceProxy::Ice::Object* upCast(::IceProxy::FriendDetector::Recognizer*);

}

namespace FriendDetector
{

typedef ::IceInternal::Handle< ::FriendDetector::Recognizer> RecognizerPtr;
typedef ::IceInternal::ProxyHandle< ::IceProxy::FriendDetector::Recognizer> RecognizerPrx;

void __read(::IceInternal::BasicStream*, RecognizerPrx&);
void __patch__RecognizerPtr(void*, ::Ice::ObjectPtr&);

}

namespace FriendDetector
{

typedef ::std::vector< ::Ice::Byte> File;

typedef ::std::vector< ::FriendDetector::File> Files;
void __writeFiles(::IceInternal::BasicStream*, const ::FriendDetector::File*, const ::FriendDetector::File*);
void __readFiles(::IceInternal::BasicStream*, Files&);

struct FacePosition
{
    ::Ice::Int left;
    ::Ice::Int top;
    ::Ice::Int right;
    ::Ice::Int bottom;

    bool operator==(const FacePosition&) const;
    bool operator<(const FacePosition&) const;
    bool operator!=(const FacePosition& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const FacePosition& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const FacePosition& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const FacePosition& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::FriendDetector::FacePosition> FacePositions;
void __writeFacePositions(::IceInternal::BasicStream*, const ::FriendDetector::FacePosition*, const ::FriendDetector::FacePosition*);
void __readFacePositions(::IceInternal::BasicStream*, FacePositions&);

struct Face
{
    ::FriendDetector::FacePosition position;
    ::std::string name;

    bool operator==(const Face&) const;
    bool operator<(const Face&) const;
    bool operator!=(const Face& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const Face& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const Face& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const Face& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::FriendDetector::Face> Faces;
void __writeFaces(::IceInternal::BasicStream*, const ::FriendDetector::Face*, const ::FriendDetector::Face*);
void __readFaces(::IceInternal::BasicStream*, Faces&);

struct FacePictureWithName
{
    ::Ice::Int id;
    ::FriendDetector::File jpegFileOfFace;
    ::std::string name;

    bool operator==(const FacePictureWithName&) const;
    bool operator<(const FacePictureWithName&) const;
    bool operator!=(const FacePictureWithName& __rhs) const
    {
        return !operator==(__rhs);
    }
    bool operator<=(const FacePictureWithName& __rhs) const
    {
        return operator<(__rhs) || operator==(__rhs);
    }
    bool operator>(const FacePictureWithName& __rhs) const
    {
        return !operator<(__rhs) && !operator==(__rhs);
    }
    bool operator>=(const FacePictureWithName& __rhs) const
    {
        return !operator<(__rhs);
    }

    void __write(::IceInternal::BasicStream*) const;
    void __read(::IceInternal::BasicStream*);
};

typedef ::std::vector< ::FriendDetector::FacePictureWithName> FacePicturesWithNames;
void __writeFacePicturesWithNames(::IceInternal::BasicStream*, const ::FriendDetector::FacePictureWithName*, const ::FriendDetector::FacePictureWithName*);
void __readFacePicturesWithNames(::IceInternal::BasicStream*, FacePicturesWithNames&);

}

namespace IceProxy
{

namespace FriendDetector
{

class Recognizer : virtual public ::IceProxy::Ice::Object
{
public:

    ::FriendDetector::Faces findFacesAndRecognizePeople(const ::FriendDetector::File& jpegFile)
    {
        return findFacesAndRecognizePeople(jpegFile, 0);
    }
    ::FriendDetector::Faces findFacesAndRecognizePeople(const ::FriendDetector::File& jpegFile, const ::Ice::Context& __ctx)
    {
        return findFacesAndRecognizePeople(jpegFile, &__ctx);
    }
    
private:

    ::FriendDetector::Faces findFacesAndRecognizePeople(const ::FriendDetector::File&, const ::Ice::Context*);
    
public:

    ::std::string recognizeFace(const ::FriendDetector::File& jpegFileOfFace)
    {
        return recognizeFace(jpegFileOfFace, 0);
    }
    ::std::string recognizeFace(const ::FriendDetector::File& jpegFileOfFace, const ::Ice::Context& __ctx)
    {
        return recognizeFace(jpegFileOfFace, &__ctx);
    }
    
private:

    ::std::string recognizeFace(const ::FriendDetector::File&, const ::Ice::Context*);
    
public:

    void learn(const ::FriendDetector::File& jpegFileOfFace, const ::std::string& name)
    {
        learn(jpegFileOfFace, name, 0);
    }
    void learn(const ::FriendDetector::File& jpegFileOfFace, const ::std::string& name, const ::Ice::Context& __ctx)
    {
        learn(jpegFileOfFace, name, &__ctx);
    }
    
private:

    void learn(const ::FriendDetector::File&, const ::std::string&, const ::Ice::Context*);
    
public:

    ::FriendDetector::FacePicturesWithNames getTrainSet()
    {
        return getTrainSet(0);
    }
    ::FriendDetector::FacePicturesWithNames getTrainSet(const ::Ice::Context& __ctx)
    {
        return getTrainSet(&__ctx);
    }
    
private:

    ::FriendDetector::FacePicturesWithNames getTrainSet(const ::Ice::Context*);
    
public:

    void unLearn(::Ice::Int id)
    {
        unLearn(id, 0);
    }
    void unLearn(::Ice::Int id, const ::Ice::Context& __ctx)
    {
        unLearn(id, &__ctx);
    }
    
private:

    void unLearn(::Ice::Int, const ::Ice::Context*);
    
public:
    
    ::IceInternal::ProxyHandle<Recognizer> ice_context(const ::Ice::Context& __context) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_context(__context).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_context(__context).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_adapterId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_adapterId(__id).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_adapterId(__id).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_endpoints(const ::Ice::EndpointSeq& __endpoints) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_endpoints(__endpoints).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_endpoints(__endpoints).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_locatorCacheTimeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_locatorCacheTimeout(__timeout).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_locatorCacheTimeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_connectionCached(bool __cached) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_connectionCached(__cached).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_connectionCached(__cached).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_endpointSelection(::Ice::EndpointSelectionType __est) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_endpointSelection(__est).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_endpointSelection(__est).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_secure(bool __secure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_secure(__secure).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_secure(__secure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_preferSecure(bool __preferSecure) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_preferSecure(__preferSecure).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_preferSecure(__preferSecure).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_router(const ::Ice::RouterPrx& __router) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_router(__router).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_router(__router).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_locator(const ::Ice::LocatorPrx& __locator) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_locator(__locator).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_locator(__locator).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_collocationOptimized(bool __co) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_collocationOptimized(__co).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_collocationOptimized(__co).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_twoway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_twoway().get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_twoway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_oneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_oneway().get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_oneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_batchOneway() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_batchOneway().get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_batchOneway().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_datagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_datagram().get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_datagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_batchDatagram() const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_batchDatagram().get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_batchDatagram().get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_compress(bool __compress) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_compress(__compress).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_compress(__compress).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_timeout(int __timeout) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_timeout(__timeout).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_timeout(__timeout).get());
    #endif
    }
    
    ::IceInternal::ProxyHandle<Recognizer> ice_connectionId(const std::string& __id) const
    {
    #if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
        typedef ::IceProxy::Ice::Object _Base;
        return dynamic_cast<Recognizer*>(_Base::ice_connectionId(__id).get());
    #else
        return dynamic_cast<Recognizer*>(::IceProxy::Ice::Object::ice_connectionId(__id).get());
    #endif
    }
    
    static const ::std::string& ice_staticId();

private: 

    virtual ::IceInternal::Handle< ::IceDelegateM::Ice::Object> __createDelegateM();
    virtual ::IceInternal::Handle< ::IceDelegateD::Ice::Object> __createDelegateD();
    virtual ::IceProxy::Ice::Object* __newInstance() const;
};

}

}

namespace IceDelegate
{

namespace FriendDetector
{

class Recognizer : virtual public ::IceDelegate::Ice::Object
{
public:

    virtual ::FriendDetector::Faces findFacesAndRecognizePeople(const ::FriendDetector::File&, const ::Ice::Context*) = 0;

    virtual ::std::string recognizeFace(const ::FriendDetector::File&, const ::Ice::Context*) = 0;

    virtual void learn(const ::FriendDetector::File&, const ::std::string&, const ::Ice::Context*) = 0;

    virtual ::FriendDetector::FacePicturesWithNames getTrainSet(const ::Ice::Context*) = 0;

    virtual void unLearn(::Ice::Int, const ::Ice::Context*) = 0;
};

}

}

namespace IceDelegateM
{

namespace FriendDetector
{

class Recognizer : virtual public ::IceDelegate::FriendDetector::Recognizer,
                   virtual public ::IceDelegateM::Ice::Object
{
public:

    virtual ::FriendDetector::Faces findFacesAndRecognizePeople(const ::FriendDetector::File&, const ::Ice::Context*);

    virtual ::std::string recognizeFace(const ::FriendDetector::File&, const ::Ice::Context*);

    virtual void learn(const ::FriendDetector::File&, const ::std::string&, const ::Ice::Context*);

    virtual ::FriendDetector::FacePicturesWithNames getTrainSet(const ::Ice::Context*);

    virtual void unLearn(::Ice::Int, const ::Ice::Context*);
};

}

}

namespace IceDelegateD
{

namespace FriendDetector
{

class Recognizer : virtual public ::IceDelegate::FriendDetector::Recognizer,
                   virtual public ::IceDelegateD::Ice::Object
{
public:

    virtual ::FriendDetector::Faces findFacesAndRecognizePeople(const ::FriendDetector::File&, const ::Ice::Context*);

    virtual ::std::string recognizeFace(const ::FriendDetector::File&, const ::Ice::Context*);

    virtual void learn(const ::FriendDetector::File&, const ::std::string&, const ::Ice::Context*);

    virtual ::FriendDetector::FacePicturesWithNames getTrainSet(const ::Ice::Context*);

    virtual void unLearn(::Ice::Int, const ::Ice::Context*);
};

}

}

namespace FriendDetector
{

class Recognizer : virtual public ::Ice::Object
{
public:

    typedef RecognizerPrx ProxyType;
    typedef RecognizerPtr PointerType;
    
    virtual ::Ice::ObjectPtr ice_clone() const;

    virtual bool ice_isA(const ::std::string&, const ::Ice::Current& = ::Ice::Current()) const;
    virtual ::std::vector< ::std::string> ice_ids(const ::Ice::Current& = ::Ice::Current()) const;
    virtual const ::std::string& ice_id(const ::Ice::Current& = ::Ice::Current()) const;
    static const ::std::string& ice_staticId();

    virtual ::FriendDetector::Faces findFacesAndRecognizePeople(const ::FriendDetector::File&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___findFacesAndRecognizePeople(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::std::string recognizeFace(const ::FriendDetector::File&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___recognizeFace(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void learn(const ::FriendDetector::File&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___learn(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::FriendDetector::FacePicturesWithNames getTrainSet(const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___getTrainSet(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void unLearn(::Ice::Int, const ::Ice::Current& = ::Ice::Current()) = 0;
    ::Ice::DispatchStatus ___unLearn(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual ::Ice::DispatchStatus __dispatch(::IceInternal::Incoming&, const ::Ice::Current&);

    virtual void __write(::IceInternal::BasicStream*) const;
    virtual void __read(::IceInternal::BasicStream*, bool);
    virtual void __write(const ::Ice::OutputStreamPtr&) const;
    virtual void __read(const ::Ice::InputStreamPtr&, bool);
};

}

#endif
