// 文字コード：UTF-8
#if defined(AE_XS_DATA_INCLUDED_AE_XS_DATA_HPP)
#else
#define AE_XS_DATA_INCLUDED_AE_XS_DATA_HPP


/// @brief BigEndian環境かどうか指定するマクロオプション。
/// 指定されていなければ、__BIG_ENDIAN__が定義されているかどうかで判定。
#if defined(AE_XS_DATA_OPTION_IS_BIG_ENDIAN)
#else
    #if defined(__BIG_ENDIAN__)
        #define AE_XS_DATA_OPTION_IS_BIG_ENDIAN
    #endif
#endif

#if defined(AE_XS_DATA_OPTION_IS_BIG_ENDIAN)
    #define AE_XS_DATA_IS_BIG_ENDIAN
#else
    #define AE_XS_DATA_IS_LITTLE_ENDIAN
#endif

namespace ae {
/// Xdataのアクセサを定義する名前空間。
namespace xdata {
/// @addtogroup AeXdata
//@{

// TypeDef
typedef signed char     SInt8;
typedef signed short    SInt16;
typedef signed int      SInt32;
typedef unsigned char   UInt8;
typedef unsigned short  UInt16;
typedef unsigned int    UInt32;
typedef float           Float32;
typedef double          Float64;
typedef UInt32          Reference;

/// 文字列のヘッダ。
struct String
{
    /// 文字列データのバイト数。終端文字数は含まない。
    UInt32 byteLength;

    /// @brief 文字列データの先頭ポインタを取得する。
    /// @return 先頭ポインタ。
    const void* ptr()const
    {
        return &(&byteLength)[1];
    }

    /// @brief const char* に変換されたポインタを取得する。
    /// @return const char*に変換されたポインタ。
    const char* toCStr()const
    {
        return reinterpret_cast<const char*>(ptr());
    }
};

// 定数群。
class Constant
{
public:
    // XBIN(Xdata BINary)を示す4文字。
    static const UInt32 SIGNATURE =
    #if defined(AE_XS_DATA_IS_BIG_ENDIAN)
        0x5842494E;
#else
        0x4E494258;
#endif
        // エンディアンを示す値。
    static const UInt16 ENDIAN = 0x1234;
    // メジャーバージョン
    static const UInt8 VERSION_MAJOR = 2;
    // マイナーバージョン
    static const UInt8 VERSION_MINOR = 0;
};

// Xdataのヘッダ。
struct XdataHeader
{
    UInt32 signature;       // シグネチャ。Constant::SIGNATUREと等しい。
    UInt16 endian;          // エンディアンチェッカー。Constant::ENDIANと等しい。
    UInt8  versionMajor;    // メジャーバージョンを示す値。VERSION_MAJORに等しい。
    UInt8  versionMinor;    // マイナーバージョンを示す値。VERSION_MINOR以下。
    UInt32 datasize;        // ヘッダを含むデータサイズ。バイト数。
    UInt32 pageCode;        // 文字列のページコード。.netframeworkのページコード番号が入る。
};

/// XdataConverterで変換されたバイナリデータのアクセサ。
class Xdata
{
public:
    /// 不正なXdataとして作成。
    Xdata() : mPtr(0) {}
    /// バイナリデータの先頭アドレスを指定して作成。
    Xdata(const void* aPtr)
        : mPtr(static_cast<const XdataHeader*>(aPtr))
    {
    }

    /// @brief 保持しているポインタを取得する。
    /// @return コンストラクタで渡したポインタ。渡していなければ0。
    const void* ptr()const
    {
        return mPtr;
    }

    /// @brief 正しいXdataか取得する。
    /// @return 正当なデータならtrue。
    /// @details 
    /// デフォルトコンストラクタで作成された場合、
    /// 渡されたデータが対応できないものだった場不正なものだった場合、falseを返します。
    bool isValidData()const
    {
        return mPtr != 0
            && mPtr->signature == Constant::SIGNATURE
            && mPtr->endian == Constant::ENDIAN
            && mPtr->versionMajor == Constant::VERSION_MAJOR
            && mPtr->versionMinor <= Constant::VERSION_MINOR
            && sizeof(XdataHeader) <= mPtr->datasize
            ;
    };

    /// @brief データ本体の先頭アドレスを取得する。
    /// @return 無効なデータなら0を返す。
    const void* dataHeadAddress()const
    {
        if (!isValidData())
        {// 無効なデータなら0を。
            return 0;
        }
        return &mPtr[1];
    }

    /// @brief Referenceタグの値からLabelのアドレスを取得する。
    /// @return 無効なデータおよび無効な引数なら0を返す。
    const void* labelAddressWithReference(const Reference aReferenceValue)const
    {
        if (!isValidData())
        {// 無効なデータならNULLポインタを。
            return 0;
        }
        if (aReferenceValue < sizeof(XdataHeader) // ヘッダの中を指している
            || mPtr->datasize < aReferenceValue // データの外を指している
            )
        {// 範囲外
            return 0;
        }
        return &reinterpret_cast<const UInt8*>(mPtr)[aReferenceValue];
    }

private:
    const XdataHeader* mPtr;
};

//@}

}} // namespace
#endif
// EOF
