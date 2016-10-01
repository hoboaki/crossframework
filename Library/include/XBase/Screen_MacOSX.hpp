/**
 * @file
 * @brief Screen_EXT型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_SCREEN_MACOSX_HPP)
#else
#define XBASE_INCLUDED_SCREEN_MACOSX_HPP

//------------------------------------------------------------
struct XG3DNSOpenGLView;

//------------------------------------------------------------
namespace XBase {
    // MacOSX環境でのScreenの拡張。
    class Screen_EXT
    {
    public:        
        //============================================================
        XG3DNSOpenGLView* glView;

        //============================================================
        Screen_EXT();
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
