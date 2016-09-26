﻿/**
 * @file
 * @brief ResFileStream_STDCを記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_RESFILESTREAM_STDC_HPP)
#else
#define XBASE_INCLUDED_RESFILESTREAM_STDC_HPP

//------------------------------------------------------------
#include <cstdio>

//------------------------------------------------------------
namespace XBase {
    // C標準ライブラリ用のResFileStream拡張。
    class ResFileStream_EXT
    {
    public:
        FILE* fp;

        ResFileStream_EXT();
    };
}
//------------------------------------------------------------
#endif
// EOF
