// 文字コード：UTF-8
#include <XBase/Display.hpp>

//------------------------------------------------------------------------------
#include <XBase/Application.hpp>
#include <XBase/Ref.hpp>
#include "XBaseNSWindow.h"
#include <OpenGL/OpenGL.h>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
namespace {

const int tNormalKeyCode[256] =
{
    -1,                 // 0
    -1,                 // 1
    -1,                 // 2
    -1,                 // 3
    -1,                 // 4
    -1,                 // 5
    -1,                 // 6
    -1,                 // 7
    -1,                 // 8
    KeyKind_Tab,       // 9
    -1,                 // 10
    -1,                 // 11
    -1,                 // 12
    KeyKind_Return,    // 13
    -1,                 // 14
    -1,                 // 15
    -1,                 // 16
    -1,                 // 17
    -1,                 // 18
    -1,                 // 19
    -1,                 // 20
    -1,                 // 21
    -1,                 // 22
    -1,                 // 23
    -1,                 // 24
    -1,                 // 25
    -1,                 // 26
    KeyKind_Escape,    // 27
    -1,                 // 28
    -1,                 // 29
    -1,                 // 30
    -1,                 // 31
    KeyKind_Space,     // 32
    -1,                 // 33
    -1,                 // 34
    -1,                 // 35
    -1,                 // 36
    -1,                 // 37
    -1,                 // 38
    -1,//KeyKind_SINGLEQUOTE, // 39
    -1,                 // 40
    -1,                 // 41
    -1,                 // 42
    -1,//KeyKind_PLUS,        // 43
    -1,//KeyKind_COMMA,       // 44
    -1,//KeyKind_MINUS,       // 45
    -1,//KeyKind_DOT,         // 46
    -1,//KeyKind_SLASH,       // 47
    KeyKind_0,           // 48
    KeyKind_1,           // 49
    KeyKind_2,           // 50
    KeyKind_3,           // 51
    KeyKind_4,           // 52
    KeyKind_5,           // 53
    KeyKind_6,           // 54
    KeyKind_7,           // 55
    KeyKind_8,           // 56
    KeyKind_9,           // 57
    -1,//KeyKind_SEMICOLON,   // 58
    -1,                 // 59
    -1,                 // 60
    -1,                 // 61
    -1,                 // 62
    -1,                 // 63
    -1,                 // 64
    KeyKind_A,           // 65
    KeyKind_B,           // 66
    KeyKind_C,           // 67
    KeyKind_D,           // 68
    KeyKind_E,           // 69
    KeyKind_F,           // 70
    KeyKind_G,           // 71
    KeyKind_H,           // 72
    KeyKind_I,           // 73
    KeyKind_J,           // 74
    KeyKind_K,           // 75
    KeyKind_L,           // 76
    KeyKind_M,           // 77
    KeyKind_N,           // 78
    KeyKind_O,           // 79
    KeyKind_P,           // 80
    KeyKind_Q,           // 81
    KeyKind_R,           // 82
    KeyKind_S,           // 83
    KeyKind_T,           // 84
    KeyKind_U,           // 85
    KeyKind_V,           // 86
    KeyKind_W,           // 87
    KeyKind_X,           // 88
    KeyKind_Y,           // 89
    KeyKind_Z,           // 90
    -1,//KeyKind_LBRACKET,    // 91
    -1,//KeyKind_BACKSLASH,   // 92
    -1,//KeyKind_RBRACKET,    // 93
    -1,                 // 94
    -1,                 // 95
    -1,                 // 96
    KeyKind_A,           // 97
    KeyKind_B,           // 98
    KeyKind_C,           // 99
    KeyKind_D,           // 100
    KeyKind_E,           // 101
    KeyKind_F,           // 102
    KeyKind_G,           // 103
    KeyKind_H,           // 104
    KeyKind_I,           // 105
    KeyKind_J,           // 106
    KeyKind_K,           // 107
    KeyKind_L,           // 108
    KeyKind_M,           // 109
    KeyKind_N,           // 110
    KeyKind_O,           // 111
    KeyKind_P,           // 112
    KeyKind_Q,           // 113
    KeyKind_R,           // 114
    KeyKind_S,           // 115
    KeyKind_T,           // 116
    KeyKind_U,           // 117
    KeyKind_V,           // 118
    KeyKind_W,           // 119
    KeyKind_X,           // 120
    KeyKind_Y,           // 121
    KeyKind_Z,           // 122
    -1,//KeyKind_LBRACKET,    // 123
    -1,                 // 124
    -1,//KeyKind_RBRACKET,    // 125
    -1,//KeyKind_TILDA,       // 126
    KeyKind_BackSpace,          // 127
    -1,                 // 128
    -1,                 // 129
    -1,                 // 130
    -1,                 // 131
    -1,                 // 132
    -1,                 // 133
    -1,                 // 134
    -1,                 // 135
    -1,                 // 136
    -1,                 // 137
    -1,                 // 138
    -1,                 // 139
    -1,                 // 140
    -1,                 // 141
    -1,                 // 142
    -1,                 // 143
    -1,                 // 144
    -1,                 // 145
    -1,                 // 146
    -1,                 // 147
    -1,                 // 148
    -1,                 // 149
    -1,                 // 150
    -1,                 // 151
    -1,                 // 152
    -1,                 // 153
    -1,                 // 154
    -1,                 // 155
    -1,                 // 156
    -1,                 // 157
    -1,                 // 158
    -1,                 // 159
    -1,                 // 160
    -1,                 // 161
    -1,                 // 162
    -1,                 // 163
    -1,                 // 164
    -1,                 // 165
    -1,                 // 166
    -1,                 // 167
    -1,                 // 168
    -1,                 // 169
    -1,                 // 170
    -1,                 // 171
    -1,                 // 172
    -1,                 // 173
    -1,                 // 174
    -1,                 // 175
    -1,                 // 176
    -1,                 // 177
    -1,                 // 178
    -1,                 // 179
    -1,                 // 180
    -1,                 // 181
    -1,                 // 182
    -1,                 // 183
    -1,                 // 184
    -1,                 // 185
    -1,                 // 186
    -1,                 // 187
    -1,                 // 188
    -1,                 // 189
    -1,                 // 190
    -1,                 // 191
    -1,                 // 192
    -1,                 // 193
    -1,                 // 194
    -1,                 // 195
    -1,                 // 196
    -1,                 // 197
    -1,                 // 198
    -1,                 // 199
    -1,                 // 200
    -1,                 // 201
    -1,                 // 202
    -1,                 // 203
    -1,                 // 204
    -1,                 // 205
    -1,                 // 206
    -1,                 // 207
    -1,                 // 208
    -1,                 // 209
    -1,                 // 210
    -1,                 // 211
    -1,                 // 212
    -1,                 // 213
    -1,                 // 214
    -1,                 // 215
    -1,                 // 216
    -1,                 // 217
    -1,                 // 218
    -1,                 // 219
    -1,                 // 220
    -1,                 // 221
    -1,                 // 222
    -1,                 // 223
    -1,                 // 224
    -1,                 // 225
    -1,                 // 226
    -1,                 // 227
    -1,                 // 228
    -1,                 // 229
    -1,                 // 230
    -1,                 // 231
    -1,                 // 232
    -1,                 // 233
    -1,                 // 234
    -1,                 // 235
    -1,                 // 236
    -1,                 // 237
    -1,                 // 238
    -1,                 // 239
    -1,                 // 240
    -1,                 // 241
    -1,                 // 242
    -1,                 // 243
    -1,                 // 244
    -1,                 // 245
    -1,                 // 246
    -1,                 // 247
    -1,                 // 248
    -1,                 // 249
    -1,                 // 250
    -1,                 // 251
    -1,                 // 252
    -1,                 // 253
    -1,                 // 254
    0                  // 255
};

const int tSpecialKeyCode[256] =
{
    KeyKind_Up,           // 0
    KeyKind_Down,         // 1
    KeyKind_Left,         // 2
    KeyKind_Right,        // 3
    KeyKind_F1,           // 4
    KeyKind_F2,           // 5
    KeyKind_F3,           // 6
    KeyKind_F4,           // 7
    KeyKind_F5,           // 8
    KeyKind_F6,           // 9
    KeyKind_F7,           // 10
    KeyKind_F8,           // 11
    KeyKind_F9,           // 12
    KeyKind_F10,          // 13
    KeyKind_F11,          // 14
    KeyKind_F12,          // 15
    KeyKind_F1,           // 16 0x10
    KeyKind_F2,           // 17
    KeyKind_F3,           // 18
    KeyKind_F4,           // 19
    KeyKind_F5,           // 20
    KeyKind_F6,           // 21
    KeyKind_F7,           // 22
    KeyKind_F8,           // 23
    KeyKind_F9,           // 24
    KeyKind_F10,          // 25
    KeyKind_F11,          // 26
    KeyKind_F12,          // 27
    KeyKind_F1,           // 28
    KeyKind_F2,           // 29
    KeyKind_F3,           // 30
    KeyKind_F4,           // 31
    KeyKind_F5,           // 32 0x20
    KeyKind_F6,           // 33
    KeyKind_F7,           // 34
    KeyKind_F8,           // 35
    KeyKind_F9,           // 36
    KeyKind_F10,          // 37
    KeyKind_F11,          // 38
    KeyKind_Insert,          // 39
    KeyKind_Delete,          // 40
    KeyKind_Home,         // 41
    -1,                  // 42 Begin
    KeyKind_End,          // 43
    KeyKind_PageUp,       // 44
    KeyKind_PageDown,     // 45
    -1,//KeyKind_PrintScreen,    // 46
    KeyKind_ScrolLock,   // 47
    -1,//KeyKind_PauseBreak,   // 48 0x30
    -1,                  // 49
    -1,//KeyKind_PauseBreak,   // 50
    -1,                  // 51 Reset
    -1,                  // 52 Stop
    -1,                  // 53 Menu
    -1,                  // 54 User
    -1,                  // 55 System
    -1,//KeyKind_PRINTSCRN,    // 56
    -1,                  // 57 Clear line
    -1,                  // 58 Clear display
    -1,                  // 59 Insert line
    -1,                  // 60 Delete line
    KeyKind_Insert,          // 61
    KeyKind_Delete,          // 62
    KeyKind_PageUp,       // 63
    KeyKind_PageDown,     // 64
    -1,                  // 65 Select
    -1,                  // 66 Execute
    -1,                  // 67 Undo
    -1,                  // 68 Redo
    -1,                  // 69 Find
    -1,                  // 70 Help
    -1,                  // 71 Mode Switch
    -1,                  // 72
    -1,                  // 73
    -1,                  // 74
    -1,                  // 75
    -1,                  // 76
    -1,                  // 77
    -1,                  // 78
    -1,                  // 79
    -1,                  // 80
    -1,                  // 81
    -1,                  // 82
    -1,                  // 83
    -1,                  // 84
    -1,                  // 85
    -1,                  // 86
    -1,                  // 87
    -1,                  // 88
    -1,                  // 89
    -1,                  // 90
    -1,                  // 91
    -1,                  // 92
    -1,                  // 93
    -1,                  // 94
    -1,                  // 95
    -1,                  // 96
    -1,                  // 97
    -1,                  // 98
    -1,                  // 99
    -1,                  // 100
    -1,                  // 101
    -1,                  // 102
    -1,                  // 103
    -1,                  // 104
    -1,                  // 105
    -1,                  // 106
    -1,                  // 107
    -1,                  // 108
    -1,                  // 109
    -1,                  // 110
    -1,                  // 111
    -1,                  // 112
    -1,                  // 113
    -1,                  // 114
    -1,                  // 115
    -1,                  // 116
    -1,                  // 117
    -1,                  // 118
    -1,                  // 119
    -1,                  // 120
    -1,                  // 121
    -1,                  // 122
    -1,                  // 123
    -1,                  // 124
    -1,                  // 125
    -1,                  // 126
    -1,                  // 127
    -1,                  // 128
    -1,                  // 129
    -1,                  // 130
    -1,                  // 131
    -1,                  // 132
    -1,                  // 133
    -1,                  // 134
    -1,                  // 135
    -1,                  // 136
    -1,                  // 137
    -1,                  // 138
    -1,                  // 139
    -1,                  // 140
    -1,                  // 141
    -1,                  // 142
    -1,                  // 143
    -1,                  // 144
    -1,                  // 145
    -1,                  // 146
    -1,                  // 147
    -1,                  // 148
    -1,                  // 149
    -1,                  // 150
    -1,                  // 151
    -1,                  // 152
    -1,                  // 153
    -1,                  // 154
    -1,                  // 155
    -1,                  // 156
    -1,                  // 157
    -1,                  // 158
    -1,                  // 159
    -1,                  // 160
    -1,                  // 161
    -1,                  // 162
    -1,                  // 163
    -1,                  // 164
    -1,                  // 165
    -1,                  // 166
    -1,                  // 167
    -1,                  // 168
    -1,                  // 169
    -1,                  // 170
    -1,                  // 171
    -1,                  // 172
    -1,                  // 173
    -1,                  // 174
    -1,                  // 175
    -1,                  // 176
    -1,                  // 177
    -1,                  // 178
    -1,                  // 179
    -1,                  // 180
    -1,                  // 181
    -1,                  // 182
    -1,                  // 183
    -1,                  // 184
    -1,                  // 185
    -1,                  // 186
    -1,                  // 187
    -1,                  // 188
    -1,                  // 189
    -1,                  // 190
    -1,                  // 191
    -1,                  // 192
    -1,                  // 193
    -1,                  // 194
    -1,                  // 195
    -1,                  // 196
    -1,                  // 197
    -1,                  // 198
    -1,                  // 199
    -1,                  // 200
    -1,                  // 201
    -1,                  // 202
    -1,                  // 203
    -1,                  // 204
    -1,                  // 205
    -1,                  // 206
    -1,                  // 207
    -1,                  // 208
    -1,                  // 209
    -1,                  // 210
    -1,                  // 211
    -1,                  // 212
    -1,                  // 213
    -1,                  // 214
    -1,                  // 215
    -1,                  // 216
    -1,                  // 217
    -1,                  // 218
    -1,                  // 219
    -1,                  // 220
    -1,                  // 221
    -1,                  // 222
    -1,                  // 223
    -1,                  // 224
    -1,                  // 225
    -1,                  // 226
    -1,                  // 227
    -1,                  // 228
    -1,                  // 229
    -1,                  // 230
    -1,                  // 231
    -1,                  // 232
    -1,                  // 233
    -1,                  // 234
    -1,                  // 235
    -1,                  // 236
    -1,                  // 237
    -1,                  // 238
    -1,                  // 239
    -1,                  // 240
    -1,                  // 241
    -1,                  // 242
    -1,                  // 243
    -1,                  // 244
    -1,                  // 245
    -1,                  // 246
    -1,                  // 247
    -1,                  // 248
    -1,                  // 249
    -1,                  // 250
    -1,                  // 251
    -1,                  // 252
    -1,                  // 253
    -1,                  // 254
    -1                   // 255
};

void tUpdateModKey(KeyboardUpdateData& aData, KeyKind aKey, int aIsDown)
{
    // 同じなら何もしない
    const bool isDown = aIsDown != 0;
    if (aData.hold.get(aKey) == isDown)
    {
        return;
    }

    // 変更
    aData.hold.set(aKey, isDown);
    if (isDown)
    {
        aData.pulse.set(aKey, true);
    }
}

} // namespace

//------------------------------------------------------------------------------
uint Display::screenCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
Screen& Display::screenAtIndex(const uint aIndex)
{
    XBASE_RANGE_ASSERT_MAX(aIndex, screenCount());
    return mainScreen();
}

//------------------------------------------------------------------------------
Screen& Display::mainScreen()
{
    return *mEXT.mainScreen;
}

//------------------------------------------------------------------------------
void Display::show()
{
    mEXT.isClosed = 0;
    XBaseNSWindow_Show(mEXT.windowPtr);
}

//------------------------------------------------------------------------------
bool Display::isClosed()const
{
    return mEXT.isClosed != 0;
}

//------------------------------------------------------------------------------
void Display_EXT::CBKeyEvent(void* aOwnerPtr, const int aUnicode, const int aIsDown)
{
    // キー選択
    int keyKind = -1;
    if (0 <= aUnicode && aUnicode <= 0xFF)
    {
        keyKind = tNormalKeyCode[aUnicode];
    }
    else if (0xF700 <= aUnicode &&  aUnicode <= 0xF7FF)
    {
        keyKind = tSpecialKeyCode[aUnicode - 0xF700];
    }

    // 有効なキーなら保存
    if (0 <= keyKind)
    {
        Display_EXT* owner = static_cast<Display_EXT*>(aOwnerPtr);
        owner->keyboardUpdateData.hold.set(uint(keyKind), aIsDown != 0);
        if (aIsDown)
        {
            owner->keyboardUpdateData.pulse.set(uint(keyKind), true);
        }
    }
}

//------------------------------------------------------------------------------
void Display_EXT::CBModKeyEvent(void* aOwnerPtr, const int aIsShift, const int aIsCtrl, const int aIsAlt)
{
    Display_EXT* owner = static_cast<Display_EXT*>(aOwnerPtr);
    tUpdateModKey(owner->keyboardUpdateData, KeyKind_Shift, aIsShift);
    tUpdateModKey(owner->keyboardUpdateData, KeyKind_Ctrl, aIsCtrl);
    tUpdateModKey(owner->keyboardUpdateData, KeyKind_Alt, aIsAlt);
}

//------------------------------------------------------------------------------
void Display_EXT::CBMouseEvent(void* aOwnerPtr, const int aPressedButton, const float aX, const float aY)
{
    Display_EXT* owner = static_cast<Display_EXT*>(aOwnerPtr);
    owner->mouseUpdateData.pos.x = s16(aX);
    owner->mouseUpdateData.pos.y = s16(aY);
    owner->mouseUpdateData.posUpdated = true;
    owner->mouseUpdateData.hold.set(MouseBtnKind_L, aPressedButton & 0x01);
    owner->mouseUpdateData.hold.set(MouseBtnKind_R, aPressedButton & 0x02);
    owner->mouseUpdateData.hold.set(MouseBtnKind_M, aPressedButton & 0x04);
}

//------------------------------------------------------------------------------
Display_EXT::Display_EXT(const DisplayContext& aContext)
: windowPtr(0)
, mainScreen()
, hidPtr()
, isClosed(0)
, keyboardUpdateData()
, mouseUpdateData()
{
    // Window作成
    windowPtr = XBaseNSWindow_Create(
        aContext.locationX(),
        aContext.locationY(),
        aContext.width(),
        aContext.height(),
        this,
        &isClosed,
        CBKeyEvent,
        CBModKeyEvent,
        CBMouseEvent
        );

// メインスクリーンの作成
    mainScreen.init(Ref(*this), aContext.width(), aContext.height());
}

//------------------------------------------------------------------------------
Display_EXT::~Display_EXT()
{
    // メインスクリーンの削除
    mainScreen.reset();

    // Window解放
    XBaseNSWindow* ptr = windowPtr;
    windowPtr = 0;
    XBaseNSWindow_Destroy(ptr);
}

} // namespace
// EOF
