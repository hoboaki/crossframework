// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_XBASEUICREEN_H)
#else
#define XBASE_INCLUDED_XBASEUISCREEN_H

//------------------------------------------------------------------------------
struct XBaseUIRect
{
    float originX;
    float originY;
    float sizeW;
    float sizeH;
};

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
extern void XBaseUIScreen_GetMainScreenBounds(struct XBaseUIRect*);
#ifdef __cplusplus
}
#endif

#endif
// EOF
