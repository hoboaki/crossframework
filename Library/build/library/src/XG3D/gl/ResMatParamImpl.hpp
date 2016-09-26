﻿/**
 * @file
 * @brief ResMatParamImpl型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_RESMATPARAMIMPL_HPP)
#else
#define XG3D_INCLUDED_RESMATPARAMIMPL_HPP

//------------------------------------------------------------
#include <XBase/IAllocator.hpp>
#include <XBase/NonCopyable.hpp>
#include <XG3D/SDKHeader.hpp>
#include "BinResMatParam.hpp"
#include "XDataPlus.hpp"

//------------------------------------------------------------
namespace XG3D {
    // BinResMatParamとResMatParamの間にかますクラス。
    class ResMatParamImpl : public ::XBase::NonCopyable
    {
    public:
        const XDataPlus  xdata;
        const BinResMatParam* binPtr;

        //============================================================
        // バイナリデータの先頭アドレスを指定して作成。
        ResMatParamImpl( const ::XData::XData& aXData , const BinResMatParam* aBinPtr , ::XBase::IAllocator& aAllocator );
        ~ResMatParamImpl();
    };
}
//------------------------------------------------------------
#endif
// EOF
