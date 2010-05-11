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

#include <Recognizer.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <IceUtil/Iterator.h>
#include <IceUtil/ScopedArray.h>

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

static const ::std::string __FriendDetector__Recognizer__findFacesAndRecognizePeople_name = "findFacesAndRecognizePeople";

static const ::std::string __FriendDetector__Recognizer__recognizeFace_name = "recognizeFace";

static const ::std::string __FriendDetector__Recognizer__learn_name = "learn";

static const ::std::string __FriendDetector__Recognizer__getTrainSet_name = "getTrainSet";

static const ::std::string __FriendDetector__Recognizer__unLearn_name = "unLearn";

::Ice::Object* IceInternal::upCast(::FriendDetector::Recognizer* p) { return p; }
::IceProxy::Ice::Object* IceInternal::upCast(::IceProxy::FriendDetector::Recognizer* p) { return p; }

void
FriendDetector::__read(::IceInternal::BasicStream* __is, ::FriendDetector::RecognizerPrx& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::FriendDetector::Recognizer;
        v->__copyFrom(proxy);
    }
}

void
FriendDetector::__writeFiles(::IceInternal::BasicStream* __os, const ::FriendDetector::File* begin, const ::FriendDetector::File* end)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        if(begin[i].size() == 0)
        {
            __os->writeSize(0);
        }
        else
        {
            __os->write(&begin[i][0], &begin[i][0] + begin[i].size());
        }
    }
}

void
FriendDetector::__readFiles(::IceInternal::BasicStream* __is, ::FriendDetector::Files& v)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 1);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___v;
        __is->read(___v);
        ::std::vector< ::Ice::Byte>(___v.first, ___v.second).swap(v[i]);
        __is->endElement();
    }
    __is->endSeq(sz);
}

bool
FriendDetector::FacePosition::operator==(const FacePosition& __rhs) const
{
    if(this == &__rhs)
    {
        return true;
    }
    if(left != __rhs.left)
    {
        return false;
    }
    if(top != __rhs.top)
    {
        return false;
    }
    if(right != __rhs.right)
    {
        return false;
    }
    if(bottom != __rhs.bottom)
    {
        return false;
    }
    return true;
}

bool
FriendDetector::FacePosition::operator<(const FacePosition& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(left < __rhs.left)
    {
        return true;
    }
    else if(__rhs.left < left)
    {
        return false;
    }
    if(top < __rhs.top)
    {
        return true;
    }
    else if(__rhs.top < top)
    {
        return false;
    }
    if(right < __rhs.right)
    {
        return true;
    }
    else if(__rhs.right < right)
    {
        return false;
    }
    if(bottom < __rhs.bottom)
    {
        return true;
    }
    else if(__rhs.bottom < bottom)
    {
        return false;
    }
    return false;
}

void
FriendDetector::FacePosition::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(left);
    __os->write(top);
    __os->write(right);
    __os->write(bottom);
}

void
FriendDetector::FacePosition::__read(::IceInternal::BasicStream* __is)
{
    __is->read(left);
    __is->read(top);
    __is->read(right);
    __is->read(bottom);
}

void
FriendDetector::__writeFacePositions(::IceInternal::BasicStream* __os, const ::FriendDetector::FacePosition* begin, const ::FriendDetector::FacePosition* end)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
FriendDetector::__readFacePositions(::IceInternal::BasicStream* __is, ::FriendDetector::FacePositions& v)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->checkFixedSeq(sz, 16);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
    }
}

bool
FriendDetector::Face::operator==(const Face& __rhs) const
{
    if(this == &__rhs)
    {
        return true;
    }
    if(position != __rhs.position)
    {
        return false;
    }
    if(name != __rhs.name)
    {
        return false;
    }
    return true;
}

bool
FriendDetector::Face::operator<(const Face& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(position < __rhs.position)
    {
        return true;
    }
    else if(__rhs.position < position)
    {
        return false;
    }
    if(name < __rhs.name)
    {
        return true;
    }
    else if(__rhs.name < name)
    {
        return false;
    }
    return false;
}

void
FriendDetector::Face::__write(::IceInternal::BasicStream* __os) const
{
    position.__write(__os);
    __os->write(name);
}

void
FriendDetector::Face::__read(::IceInternal::BasicStream* __is)
{
    position.__read(__is);
    __is->read(name);
}

void
FriendDetector::__writeFaces(::IceInternal::BasicStream* __os, const ::FriendDetector::Face* begin, const ::FriendDetector::Face* end)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
FriendDetector::__readFaces(::IceInternal::BasicStream* __is, ::FriendDetector::Faces& v)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 17);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
        __is->checkSeq();
        __is->endElement();
    }
    __is->endSeq(sz);
}

bool
FriendDetector::FacePictureWithName::operator==(const FacePictureWithName& __rhs) const
{
    if(this == &__rhs)
    {
        return true;
    }
    if(id != __rhs.id)
    {
        return false;
    }
    if(jpegFileOfFace != __rhs.jpegFileOfFace)
    {
        return false;
    }
    if(name != __rhs.name)
    {
        return false;
    }
    return true;
}

bool
FriendDetector::FacePictureWithName::operator<(const FacePictureWithName& __rhs) const
{
    if(this == &__rhs)
    {
        return false;
    }
    if(id < __rhs.id)
    {
        return true;
    }
    else if(__rhs.id < id)
    {
        return false;
    }
    if(jpegFileOfFace < __rhs.jpegFileOfFace)
    {
        return true;
    }
    else if(__rhs.jpegFileOfFace < jpegFileOfFace)
    {
        return false;
    }
    if(name < __rhs.name)
    {
        return true;
    }
    else if(__rhs.name < name)
    {
        return false;
    }
    return false;
}

void
FriendDetector::FacePictureWithName::__write(::IceInternal::BasicStream* __os) const
{
    __os->write(id);
    if(jpegFileOfFace.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        __os->write(&jpegFileOfFace[0], &jpegFileOfFace[0] + jpegFileOfFace.size());
    }
    __os->write(name);
}

void
FriendDetector::FacePictureWithName::__read(::IceInternal::BasicStream* __is)
{
    __is->read(id);
    ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___jpegFileOfFace;
    __is->read(___jpegFileOfFace);
    ::std::vector< ::Ice::Byte>(___jpegFileOfFace.first, ___jpegFileOfFace.second).swap(jpegFileOfFace);
    __is->read(name);
}

void
FriendDetector::__writeFacePicturesWithNames(::IceInternal::BasicStream* __os, const ::FriendDetector::FacePictureWithName* begin, const ::FriendDetector::FacePictureWithName* end)
{
    ::Ice::Int size = static_cast< ::Ice::Int>(end - begin);
    __os->writeSize(size);
    for(int i = 0; i < size; ++i)
    {
        begin[i].__write(__os);
    }
}

void
FriendDetector::__readFacePicturesWithNames(::IceInternal::BasicStream* __is, ::FriendDetector::FacePicturesWithNames& v)
{
    ::Ice::Int sz;
    __is->readSize(sz);
    __is->startSeq(sz, 6);
    v.resize(sz);
    for(int i = 0; i < sz; ++i)
    {
        v[i].__read(__is);
        __is->checkSeq();
        __is->endElement();
    }
    __is->endSeq(sz);
}

::FriendDetector::Faces
IceProxy::FriendDetector::Recognizer::findFacesAndRecognizePeople(const ::FriendDetector::File& jpegFile, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
#if defined(__BCPLUSPLUS__) && (__BCPLUSPLUS__ >= 0x0600) // C++Builder 2009 compiler bug
            IceUtil::DummyBCC dummy;
#endif
            __checkTwowayOnly(__FriendDetector__Recognizer__findFacesAndRecognizePeople_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::FriendDetector::Recognizer* __del = dynamic_cast< ::IceDelegate::FriendDetector::Recognizer*>(__delBase.get());
            return __del->findFacesAndRecognizePeople(jpegFile, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, 0);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, 0, __cnt);
        }
    }
}

::std::string
IceProxy::FriendDetector::Recognizer::recognizeFace(const ::FriendDetector::File& jpegFileOfFace, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
#if defined(__BCPLUSPLUS__) && (__BCPLUSPLUS__ >= 0x0600) // C++Builder 2009 compiler bug
            IceUtil::DummyBCC dummy;
#endif
            __checkTwowayOnly(__FriendDetector__Recognizer__recognizeFace_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::FriendDetector::Recognizer* __del = dynamic_cast< ::IceDelegate::FriendDetector::Recognizer*>(__delBase.get());
            return __del->recognizeFace(jpegFileOfFace, __ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, 0);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, 0, __cnt);
        }
    }
}

void
IceProxy::FriendDetector::Recognizer::learn(const ::FriendDetector::File& jpegFileOfFace, const ::std::string& name, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
#if defined(__BCPLUSPLUS__) && (__BCPLUSPLUS__ >= 0x0600) // C++Builder 2009 compiler bug
            IceUtil::DummyBCC dummy;
#endif
            __delBase = __getDelegate(false);
            ::IceDelegate::FriendDetector::Recognizer* __del = dynamic_cast< ::IceDelegate::FriendDetector::Recognizer*>(__delBase.get());
            __del->learn(jpegFileOfFace, name, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, 0);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, 0, __cnt);
        }
    }
}

::FriendDetector::FacePicturesWithNames
IceProxy::FriendDetector::Recognizer::getTrainSet(const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
#if defined(__BCPLUSPLUS__) && (__BCPLUSPLUS__ >= 0x0600) // C++Builder 2009 compiler bug
            IceUtil::DummyBCC dummy;
#endif
            __checkTwowayOnly(__FriendDetector__Recognizer__getTrainSet_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::FriendDetector::Recognizer* __del = dynamic_cast< ::IceDelegate::FriendDetector::Recognizer*>(__delBase.get());
            return __del->getTrainSet(__ctx);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, 0);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, 0, __cnt);
        }
    }
}

void
IceProxy::FriendDetector::Recognizer::unLearn(::Ice::Int id, const ::Ice::Context* __ctx)
{
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
#if defined(__BCPLUSPLUS__) && (__BCPLUSPLUS__ >= 0x0600) // C++Builder 2009 compiler bug
            IceUtil::DummyBCC dummy;
#endif
            __delBase = __getDelegate(false);
            ::IceDelegate::FriendDetector::Recognizer* __del = dynamic_cast< ::IceDelegate::FriendDetector::Recognizer*>(__delBase.get());
            __del->unLearn(id, __ctx);
            return;
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, 0);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, 0, __cnt);
        }
    }
}

const ::std::string&
IceProxy::FriendDetector::Recognizer::ice_staticId()
{
    return ::FriendDetector::Recognizer::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::FriendDetector::Recognizer::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::FriendDetector::Recognizer);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::FriendDetector::Recognizer::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::FriendDetector::Recognizer);
}

::IceProxy::Ice::Object*
IceProxy::FriendDetector::Recognizer::__newInstance() const
{
    return new Recognizer;
}

::FriendDetector::Faces
IceDelegateM::FriendDetector::Recognizer::findFacesAndRecognizePeople(const ::FriendDetector::File& jpegFile, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __FriendDetector__Recognizer__findFacesAndRecognizePeople_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        if(jpegFile.size() == 0)
        {
            __os->writeSize(0);
        }
        else
        {
            __os->write(&jpegFile[0], &jpegFile[0] + jpegFile.size());
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    ::FriendDetector::Faces __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.is();
        __is->startReadEncaps();
        ::FriendDetector::__readFaces(__is, __ret);
        __is->endReadEncaps();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::std::string
IceDelegateM::FriendDetector::Recognizer::recognizeFace(const ::FriendDetector::File& jpegFileOfFace, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __FriendDetector__Recognizer__recognizeFace_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        if(jpegFileOfFace.size() == 0)
        {
            __os->writeSize(0);
        }
        else
        {
            __os->write(&jpegFileOfFace[0], &jpegFileOfFace[0] + jpegFileOfFace.size());
        }
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    ::std::string __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.is();
        __is->startReadEncaps();
        __is->read(__ret);
        __is->endReadEncaps();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::FriendDetector::Recognizer::learn(const ::FriendDetector::File& jpegFileOfFace, const ::std::string& name, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __FriendDetector__Recognizer__learn_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        if(jpegFileOfFace.size() == 0)
        {
            __os->writeSize(0);
        }
        else
        {
            __os->write(&jpegFileOfFace[0], &jpegFileOfFace[0] + jpegFileOfFace.size());
        }
        __os->write(name);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    if(!__og.is()->b.empty())
    {
        try
        {
            if(!__ok)
            {
                try
                {
                    __og.throwUserException();
                }
                catch(const ::Ice::UserException& __ex)
                {
                    ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                    throw __uue;
                }
            }
            __og.is()->skipEmptyEncaps();
        }
        catch(const ::Ice::LocalException& __ex)
        {
            throw ::IceInternal::LocalExceptionWrapper(__ex, false);
        }
    }
}

::FriendDetector::FacePicturesWithNames
IceDelegateM::FriendDetector::Recognizer::getTrainSet(const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __FriendDetector__Recognizer__getTrainSet_name, ::Ice::Normal, __context);
    bool __ok = __og.invoke();
    ::FriendDetector::FacePicturesWithNames __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.is();
        __is->startReadEncaps();
        ::FriendDetector::__readFacePicturesWithNames(__is, __ret);
        __is->endReadEncaps();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

void
IceDelegateM::FriendDetector::Recognizer::unLearn(::Ice::Int id, const ::Ice::Context* __context)
{
    ::IceInternal::Outgoing __og(__handler.get(), __FriendDetector__Recognizer__unLearn_name, ::Ice::Normal, __context);
    try
    {
        ::IceInternal::BasicStream* __os = __og.os();
        __os->write(id);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    if(!__og.is()->b.empty())
    {
        try
        {
            if(!__ok)
            {
                try
                {
                    __og.throwUserException();
                }
                catch(const ::Ice::UserException& __ex)
                {
                    ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                    throw __uue;
                }
            }
            __og.is()->skipEmptyEncaps();
        }
        catch(const ::Ice::LocalException& __ex)
        {
            throw ::IceInternal::LocalExceptionWrapper(__ex, false);
        }
    }
}

::FriendDetector::Faces
IceDelegateD::FriendDetector::Recognizer::findFacesAndRecognizePeople(const ::FriendDetector::File& jpegFile, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::FriendDetector::Faces& __result, const ::FriendDetector::File& jpegFile, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_jpegFile(jpegFile)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::FriendDetector::Recognizer* servant = dynamic_cast< ::FriendDetector::Recognizer*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->findFacesAndRecognizePeople(_m_jpegFile, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::FriendDetector::Faces& _result;
        const ::FriendDetector::File& _m_jpegFile;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __FriendDetector__Recognizer__findFacesAndRecognizePeople_name, ::Ice::Normal, __context);
    ::FriendDetector::Faces __result;
    try
    {
        _DirectI __direct(__result, jpegFile, __current);
        try
        {
            __direct.servant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

::std::string
IceDelegateD::FriendDetector::Recognizer::recognizeFace(const ::FriendDetector::File& jpegFileOfFace, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::std::string& __result, const ::FriendDetector::File& jpegFileOfFace, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_jpegFileOfFace(jpegFileOfFace)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::FriendDetector::Recognizer* servant = dynamic_cast< ::FriendDetector::Recognizer*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->recognizeFace(_m_jpegFileOfFace, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::std::string& _result;
        const ::FriendDetector::File& _m_jpegFileOfFace;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __FriendDetector__Recognizer__recognizeFace_name, ::Ice::Normal, __context);
    ::std::string __result;
    try
    {
        _DirectI __direct(__result, jpegFileOfFace, __current);
        try
        {
            __direct.servant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

void
IceDelegateD::FriendDetector::Recognizer::learn(const ::FriendDetector::File& jpegFileOfFace, const ::std::string& name, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(const ::FriendDetector::File& jpegFileOfFace, const ::std::string& name, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _m_jpegFileOfFace(jpegFileOfFace),
            _m_name(name)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::FriendDetector::Recognizer* servant = dynamic_cast< ::FriendDetector::Recognizer*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            servant->learn(_m_jpegFileOfFace, _m_name, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        const ::FriendDetector::File& _m_jpegFileOfFace;
        const ::std::string& _m_name;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __FriendDetector__Recognizer__learn_name, ::Ice::Normal, __context);
    try
    {
        _DirectI __direct(jpegFileOfFace, name, __current);
        try
        {
            __direct.servant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
}

::FriendDetector::FacePicturesWithNames
IceDelegateD::FriendDetector::Recognizer::getTrainSet(const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::FriendDetector::FacePicturesWithNames& __result, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::FriendDetector::Recognizer* servant = dynamic_cast< ::FriendDetector::Recognizer*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->getTrainSet(_current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::FriendDetector::FacePicturesWithNames& _result;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __FriendDetector__Recognizer__getTrainSet_name, ::Ice::Normal, __context);
    ::FriendDetector::FacePicturesWithNames __result;
    try
    {
        _DirectI __direct(__result, __current);
        try
        {
            __direct.servant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

void
IceDelegateD::FriendDetector::Recognizer::unLearn(::Ice::Int id, const ::Ice::Context* __context)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::Ice::Int id, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _m_id(id)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::FriendDetector::Recognizer* servant = dynamic_cast< ::FriendDetector::Recognizer*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            servant->unLearn(_m_id, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::Ice::Int _m_id;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __FriendDetector__Recognizer__unLearn_name, ::Ice::Normal, __context);
    try
    {
        _DirectI __direct(id, __current);
        try
        {
            __direct.servant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
}

::Ice::ObjectPtr
FriendDetector::Recognizer::ice_clone() const
{
    throw ::Ice::CloneNotImplementedException(__FILE__, __LINE__);
    return 0; // to avoid a warning with some compilers
}

static const ::std::string __FriendDetector__Recognizer_ids[2] =
{
    "::FriendDetector::Recognizer",
    "::Ice::Object"
};

bool
FriendDetector::Recognizer::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__FriendDetector__Recognizer_ids, __FriendDetector__Recognizer_ids + 2, _s);
}

::std::vector< ::std::string>
FriendDetector::Recognizer::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__FriendDetector__Recognizer_ids[0], &__FriendDetector__Recognizer_ids[2]);
}

const ::std::string&
FriendDetector::Recognizer::ice_id(const ::Ice::Current&) const
{
    return __FriendDetector__Recognizer_ids[0];
}

const ::std::string&
FriendDetector::Recognizer::ice_staticId()
{
    return __FriendDetector__Recognizer_ids[0];
}

::Ice::DispatchStatus
FriendDetector::Recognizer::___findFacesAndRecognizePeople(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::FriendDetector::File jpegFile;
    ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___jpegFile;
    __is->read(___jpegFile);
    ::std::vector< ::Ice::Byte>(___jpegFile.first, ___jpegFile.second).swap(jpegFile);
    __is->endReadEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::FriendDetector::Faces __ret = findFacesAndRecognizePeople(jpegFile, __current);
    if(__ret.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::FriendDetector::__writeFaces(__os, &__ret[0], &__ret[0] + __ret.size());
    }
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
FriendDetector::Recognizer::___recognizeFace(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::FriendDetector::File jpegFileOfFace;
    ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___jpegFileOfFace;
    __is->read(___jpegFileOfFace);
    ::std::vector< ::Ice::Byte>(___jpegFileOfFace.first, ___jpegFileOfFace.second).swap(jpegFileOfFace);
    __is->endReadEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::std::string __ret = recognizeFace(jpegFileOfFace, __current);
    __os->write(__ret);
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
FriendDetector::Recognizer::___learn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::FriendDetector::File jpegFileOfFace;
    ::std::string name;
    ::std::pair<const ::Ice::Byte*, const ::Ice::Byte*> ___jpegFileOfFace;
    __is->read(___jpegFileOfFace);
    ::std::vector< ::Ice::Byte>(___jpegFileOfFace.first, ___jpegFileOfFace.second).swap(jpegFileOfFace);
    __is->read(name);
    __is->endReadEncaps();
    learn(jpegFileOfFace, name, __current);
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
FriendDetector::Recognizer::___getTrainSet(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    __inS.is()->skipEmptyEncaps();
    ::IceInternal::BasicStream* __os = __inS.os();
    ::FriendDetector::FacePicturesWithNames __ret = getTrainSet(__current);
    if(__ret.size() == 0)
    {
        __os->writeSize(0);
    }
    else
    {
        ::FriendDetector::__writeFacePicturesWithNames(__os, &__ret[0], &__ret[0] + __ret.size());
    }
    return ::Ice::DispatchOK;
}

::Ice::DispatchStatus
FriendDetector::Recognizer::___unLearn(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.is();
    __is->startReadEncaps();
    ::Ice::Int id;
    __is->read(id);
    __is->endReadEncaps();
    unLearn(id, __current);
    return ::Ice::DispatchOK;
}

static ::std::string __FriendDetector__Recognizer_all[] =
{
    "findFacesAndRecognizePeople",
    "getTrainSet",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping",
    "learn",
    "recognizeFace",
    "unLearn"
};

::Ice::DispatchStatus
FriendDetector::Recognizer::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< ::std::string*, ::std::string*> r = ::std::equal_range(__FriendDetector__Recognizer_all, __FriendDetector__Recognizer_all + 9, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __FriendDetector__Recognizer_all)
    {
        case 0:
        {
            return ___findFacesAndRecognizePeople(in, current);
        }
        case 1:
        {
            return ___getTrainSet(in, current);
        }
        case 2:
        {
            return ___ice_id(in, current);
        }
        case 3:
        {
            return ___ice_ids(in, current);
        }
        case 4:
        {
            return ___ice_isA(in, current);
        }
        case 5:
        {
            return ___ice_ping(in, current);
        }
        case 6:
        {
            return ___learn(in, current);
        }
        case 7:
        {
            return ___recognizeFace(in, current);
        }
        case 8:
        {
            return ___unLearn(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
FriendDetector::Recognizer::__write(::IceInternal::BasicStream* __os) const
{
    __os->writeTypeId(ice_staticId());
    __os->startWriteSlice();
    __os->endWriteSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__write(__os);
#else
    ::Ice::Object::__write(__os);
#endif
}

void
FriendDetector::Recognizer::__read(::IceInternal::BasicStream* __is, bool __rid)
{
    if(__rid)
    {
        ::std::string myId;
        __is->readTypeId(myId);
    }
    __is->startReadSlice();
    __is->endReadSlice();
#if defined(_MSC_VER) && (_MSC_VER < 1300) // VC++ 6 compiler bug
    Object::__read(__is, true);
#else
    ::Ice::Object::__read(__is, true);
#endif
}

void
FriendDetector::Recognizer::__write(const ::Ice::OutputStreamPtr&) const
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type FriendDetector::Recognizer was not generated with stream support";
    throw ex;
}

void
FriendDetector::Recognizer::__read(const ::Ice::InputStreamPtr&, bool)
{
    Ice::MarshalException ex(__FILE__, __LINE__);
    ex.reason = "type FriendDetector::Recognizer was not generated with stream support";
    throw ex;
}

void 
FriendDetector::__patch__RecognizerPtr(void* __addr, ::Ice::ObjectPtr& v)
{
    ::FriendDetector::RecognizerPtr* p = static_cast< ::FriendDetector::RecognizerPtr*>(__addr);
    assert(p);
    *p = ::FriendDetector::RecognizerPtr::dynamicCast(v);
    if(v && !*p)
    {
        IceInternal::Ex::throwUOE(::FriendDetector::Recognizer::ice_staticId(), v->ice_id());
    }
}

bool
FriendDetector::operator==(const ::FriendDetector::Recognizer& l, const ::FriendDetector::Recognizer& r)
{
    return static_cast<const ::Ice::Object&>(l) == static_cast<const ::Ice::Object&>(r);
}

bool
FriendDetector::operator<(const ::FriendDetector::Recognizer& l, const ::FriendDetector::Recognizer& r)
{
    return static_cast<const ::Ice::Object&>(l) < static_cast<const ::Ice::Object&>(r);
}
