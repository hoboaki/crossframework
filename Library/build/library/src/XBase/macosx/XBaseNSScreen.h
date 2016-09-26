/**
 * @file
 * @brief NSScreenのラッパー関数を定義する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_XBASENSSCREEN_H)
#else
#define XBASE_INCLUDED_XBASENSSCREEN_H

//-----------------------------------------------------------
struct XBaseNSRect
{
    float originX;
    float originY;
    float sizeW;
    float sizeH;
};

//-----------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    extern void XBaseNSScreen_GetMainScreenFrame( struct XBaseNSRect* );
    extern void XBaseNSScreen_GetMainScreenVisibleFrame( struct XBaseNSRect* );
#ifdef __cplusplus
}
#endif
//-----------------------------------------------------------
#endif
//-----------------------------------------------------------
// EOF
