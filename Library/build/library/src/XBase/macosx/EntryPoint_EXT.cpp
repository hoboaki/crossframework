// 文字コード：UTF-8
#include <XBase/EntryPoint.hpp>

//------------------------------------------------------------------------------
#include <XBase/Application.hpp>
#include <XBase/Argument.hpp>
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
extern "C" int mainC(int aArgCount, const char* aArgValues[], const char* aExeFileName, const char* aExeDirPath);
int mainC(
    const int aArgCount,
    const char* aArgValues[],
    const char* aExeFileName,
    const char* aExeDirPath
    )
{
    // 引数作成
    const int offset = 1; // Exeのパスは別で処理しているためパス。
    XBASE_RANGE_ASSERT_EMIN(offset, aArgCount);
    const ::XBase::Argument arg(
        ::XBase::uint(aArgCount - offset),
        &aArgValues[offset],
        aExeFileName,
        aExeDirPath
        );

// アプリケーション作成
    ::XBase::Application app(arg);

    // 実行
    return xmain(app);
}

//------------------------------------------------------------------------------
// EOF
