// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_KEYKIND_HPP)
#else
#define XBASE_INCLUDED_KEYKIND_HPP

//------------------------------------------------------------------------------
namespace XBase {

/// @addtogroup XBase-Hid
//@{
/// キーボードのキーの種類。
enum KeyKind
{
    KeyKind_BackSpace,
    KeyKind_Tab,
    KeyKind_Return,
    KeyKind_Pause,
    KeyKind_Escape,
    KeyKind_Space,
    KeyKind_Delete,

    KeyKind_0,
    KeyKind_1,
    KeyKind_2,
    KeyKind_3,
    KeyKind_4,
    KeyKind_5,
    KeyKind_6,
    KeyKind_7,
    KeyKind_8,
    KeyKind_9,
    KeyKind_A,
    KeyKind_B,
    KeyKind_C,
    KeyKind_D,
    KeyKind_E,
    KeyKind_F,
    KeyKind_G,
    KeyKind_H,
    KeyKind_I,
    KeyKind_J,
    KeyKind_K,
    KeyKind_L,
    KeyKind_M,
    KeyKind_N,
    KeyKind_O,
    KeyKind_P,
    KeyKind_Q,
    KeyKind_R,
    KeyKind_S,
    KeyKind_T,
    KeyKind_U,
    KeyKind_V,
    KeyKind_W,
    KeyKind_X,
    KeyKind_Y,
    KeyKind_Z,
    /* End of ASCII mapped keysyms */

    /* Arrows + Home/End pad */
    KeyKind_Up,
    KeyKind_Down,
    KeyKind_Right,
    KeyKind_Left,
    KeyKind_Insert,
    KeyKind_Home,
    KeyKind_End,
    KeyKind_PageUp,
    KeyKind_PageDown,

    /* Function keys */
    KeyKind_F1,
    KeyKind_F2,
    KeyKind_F3,
    KeyKind_F4,
    KeyKind_F5,
    KeyKind_F6,
    KeyKind_F7,
    KeyKind_F8,
    KeyKind_F9,
    KeyKind_F10,
    KeyKind_F11,
    KeyKind_F12,
    KeyKind_F13,
    KeyKind_F14,
    KeyKind_F15,

    /* Key state modifier keys */
    KeyKind_NumLock,
    KeyKind_CapsLock,
    KeyKind_ScrolLock,
    KeyKind_Shift,
    KeyKind_Ctrl,
    KeyKind_Alt,

    // term
    KeyKind_TERMINATE,
    KeyKind_MIN = 0,
    KeyKind_MAX = KeyKind_TERMINATE - 1
};
//@}

} // namespace
#endif
// EOF
