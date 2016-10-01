// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_SCREEN_IOS_HPP)
#else
#define XBASE_INCLUDED_SCREEN_IOS_HPP

//------------------------------------------------------------------------------
struct XG3DUIOpenGLView;

//------------------------------------------------------------------------------
namespace XBase {
    // iOS環境でのScreenの拡張。
    class Screen_EXT
    {
    public:        
        //============================================================
        XG3DUIOpenGLView* glView;

        //============================================================
        Screen_EXT();
    };
//@}

} // namespace
#endif
// EOF
