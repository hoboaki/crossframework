// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_ENTRYPOINT_HPP)
#else
#define XBASE_INCLUDED_ENTRYPOINT_HPP

//------------------------------------------------------------------------------
namespace XBase {

class Application;
}

/// @addtogroup XBase-System
//@{

/// @brief メイン関数の宣言。
/// @return リターンコード。
/// @details アプリケーションはこれを実装してアプリケーションを開始してください。
/// @code
/// // 例
/// int xmain( const ::XBase::Application& )
/// {
///     // 何もせずにアプリケーションを終了するコード。
///     return 0;
/// }
/// @endcode
extern int xmain(::XBase::Application& aApp);

//@}
#endif
// EOF
