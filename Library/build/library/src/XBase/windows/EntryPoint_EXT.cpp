// 文字コード：UTF-8
#include <XBase/EntryPoint.hpp>

//------------------------------------------------------------------------------
#include <XBase/Application.hpp>
#include <XBase/Argument.hpp>
#include <XBase/Config.hpp>
#include <XBase/Console.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/SDKHeader.hpp>
#include <XBase/StringTraits.hpp>
#include <XBase/Unused.hpp>

//------------------------------------------------------------------------------
#pragma warning(disable: 4996)

//------------------------------------------------------------------------------
namespace {

enum
{
    tExeFilePathLength = 260,  // Windowsのファイル名はパスを含めて最長260文字。
    tExeFileNameLength = 260,
    tExeDirPathLength = 260,
    tArgCharsLength = 8192, // WindowsXP以降のコマンドライン引数の最長。
    tArgPtrsLength = ::XBase::Argument::ArgCountMax
};

bool  tIsConsole = false;
char  tExeFilePath[tExeFilePathLength];
char  tExeFileName[tExeFileNameLength];
char  tExeDirPath[tExeDirPathLength];
int tArgCount = 0;
char  tArgChars[tArgCharsLength];
char* tArgPtrs[tArgPtrsLength];

// 指定の文字の最後のindex値取得。
int tLastIndexOf(const char aCh, const char* aStr)
{
    XBASE_ASSERT_POINTER(aStr);
    int index = -1;
    for (int i = 0; aStr[i] != '\0'; ++i) {
        if (aStr[i] == aCh) {
            index = i;
        }
    }
    return index;
}

// 文字置き換え。
void tReplaceChar(const char aTargetCh, const char aNewCh, char* aStr)
{
    XBASE_ASSERT_POINTER(aStr);
    for (int i = 0; aStr[i] != '\0'; ++i) {
        if (aStr[i] == aTargetCh) {
            aStr[i] = aNewCh;
        }
    }
}

// tExeFilePathからtExeFileName,tExeDirPathを設定する
void tSetupExeInfo()
{
    // 最後の'\'の位置
    const int dirPathLength = tLastIndexOf('\\', tExeFilePath);
    XBASE_ASSERT_MIN_TERM(0, dirPathLength, int(tExeDirPathLength));

    // ディレクトリパス
    ::XBase::StringTraits< char >::NCopy(tExeDirPath, tExeDirPathLength, tExeFilePath);
    tExeDirPath[dirPathLength] = '\0';
    tReplaceChar('\\', '/', tExeDirPath);

    // ファイル名
    ::XBase::StringTraits< char >::NCopy(tExeFileName, tExeFileNameLength, &tExeFilePath[dirPathLength + 1]);
}

// 空白文字か
bool tIsWhiteCh(const char aCh)
{
    switch (aCh) {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            return true;
        default:
            break;
    }
    return false;
}

// tArgCharsからtArgCountとaArgPtrsを設定する。
void tSetupArg()
{
    int index = 0;
    while (tArgChars[index] != '\0') {
        // 空白文字をスキップする
        while (tIsWhiteCh(tArgChars[index])) {
            ++index;
        }

        // 0なら何もせず終了
        if (tArgChars[index] == '\0') {
            break;
        }

        // 最初の文字で分岐
        if (tArgChars[index] == '\"') {
            // ダブルコーテーション
            // 次の文字からスタート
            ++index;

            // 先頭が0なら何もせず終了
            if (tArgChars[index] == '\0') {
                break;
            }

            // 先頭ポインタ設定
            tArgPtrs[tArgCount] = &tArgChars[index];

            // 次のダブルコーテーションまで探す
            while (tArgChars[index] != '\0'
                && tArgChars[index] != '\"'
                )
            {
                ++index;
            }

            // 現在のindex値に\0を入れる
            tArgChars[index] = '\0';
            ++index;
            ++tArgCount;
        }
        else
        {// 通常
            // 先頭ポインタ設定
            tArgPtrs[tArgCount] = &tArgChars[index];

            // 空白文字が見つかるまで進める
            while (!tIsWhiteCh(tArgChars[index])) {
                ++index;
            }

            // 現在のindex値に\0を入れる
            tArgChars[index] = '\0';
            ++index;
            ++tArgCount;
        }
    }
}

// main関数の共通部分。
int tWinMainIN(
    HINSTANCE aInstance,
    int aCmdShow
    )
{
    // 引数の作成
    const ::XBase::Argument arg(
        tArgCount,
        tArgPtrs,
        tExeFileName,
        tExeDirPath
        );
    XBASE_UNUSED(aInstance);
    XBASE_UNUSED(aCmdShow);

    // アプリケーション作成
    ::XBase::Application app(arg);

    // 実行
    return ::xmain(app);
}

} // namespace

//------------------------------------------------------------------------------
int WINAPI WinMain(
    HINSTANCE aInstance,
    HINSTANCE aPrevInstance,
    LPSTR aCmdLine,
    int aCmdShow
    )
{
    // 実行ファイルのパス
    GetModuleFileNameA(aInstance, tExeFilePath, tExeFilePathLength);
    tSetupExeInfo();

    // 引数の解析
    {
        // まずコピー
        ::XBase::StringTraits< char >::NCopy(tArgChars, tArgCharsLength, aCmdLine);

        // 解析開始
        tSetupArg();
    }

    // 引数の作成
    XBASE_UNUSED(aInstance);
    XBASE_UNUSED(aPrevInstance);
    XBASE_UNUSED(aCmdLine);
    XBASE_UNUSED(aCmdShow);
    /// @todo 引数の解析

    // 実行
    return tWinMainIN(aInstance, aCmdShow);
}

//------------------------------------------------------------------------------
#if !defined(XBASE_FINAL)
int main(
    const int aArgCount,
    const char* aArgValues[]
    )
{
    // フラグオン
    tIsConsole = true;

    // [0]は実行ファイルのフルパス
    // C:\dirname\FileName.exe といった文字列が入っている。
    {
        // フルパス取得
        XBASE_ASSERT_LESS_EQUALS(1, aArgCount);
        const char* fullPath = aArgValues[0];

        // フルパスを設定
        ::XBase::StringTraits< char >::NCopy(tExeFilePath, tExeFilePathLength, fullPath);

        // セットアップ
        tSetupExeInfo();
    }

    {// 引数
        int index = 0;
        for (int i = 1; i < aArgCount && i < tArgPtrsLength; ++i) {
            const ::XBase::StringTraits< char >::WriteResult result =
                ::XBase::StringTraits< char >::NCopy(tArgChars, tArgCharsLength - index, aArgValues[i]);
            tArgPtrs[i] = &tArgChars[index];
            index += ::XBase::uint(result.length + 1);
        }
        tArgCount = ::XBase::uint(aArgCount - 1);
    }

    // 実行
    return tWinMainIN((HINSTANCE)GetModuleHandle(NULL), SW_SHOWNORMAL);
}
#endif

// EOF
