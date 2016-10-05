// 文字コード：UTF-8
#include <XBase/Display.hpp>

//------------------------------------------------------------------------------
#include <XBase/Application.hpp>
#include <XBase/KeyKind.hpp>
#include <XBase/Hid.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/Ref.hpp>
#include <XBase/Unused.hpp>
#include <XBase/SdkHeader.hpp>

//------------------------------------------------------------------------------
namespace XBase {

//------------------------------------------------------------------------------
namespace {

Pointer< Display_Ext > tCurrentDisplay;

KeyKind tToKeyKind(WPARAM aKey)
{
    switch (aKey) {
        case VK_BACK:   return KeyKind_BackSpace;
        case VK_TAB:    return KeyKind_Tab;
        case VK_RETURN: return KeyKind_Return;
        case VK_PAUSE:  return KeyKind_Pause;
        case VK_ESCAPE: return KeyKind_Escape;
        case VK_SPACE:  return KeyKind_Space;
        case VK_DELETE: return KeyKind_Delete;

        case '0': return KeyKind_0;
        case '1': return KeyKind_1;
        case '2': return KeyKind_2;
        case '3': return KeyKind_3;
        case '4': return KeyKind_4;
        case '5': return KeyKind_5;
        case '6': return KeyKind_6;
        case '7': return KeyKind_7;
        case '8': return KeyKind_8;
        case '9': return KeyKind_9;
        case 'A': return KeyKind_A;
        case 'B': return KeyKind_B;
        case 'C': return KeyKind_C;
        case 'D': return KeyKind_D;
        case 'E': return KeyKind_E;
        case 'F': return KeyKind_F;
        case 'G': return KeyKind_G;
        case 'H': return KeyKind_H;
        case 'I': return KeyKind_I;
        case 'J': return KeyKind_J;
        case 'K': return KeyKind_K;
        case 'L': return KeyKind_L;
        case 'M': return KeyKind_M;
        case 'N': return KeyKind_N;
        case 'O': return KeyKind_O;
        case 'P': return KeyKind_P;
        case 'Q': return KeyKind_Q;
        case 'R': return KeyKind_R;
        case 'S': return KeyKind_S;
        case 'T': return KeyKind_T;
        case 'U': return KeyKind_U;
        case 'V': return KeyKind_V;
        case 'W': return KeyKind_W;
        case 'X': return KeyKind_X;
        case 'Y': return KeyKind_Y;
        case 'Z': return KeyKind_Z;

        #if 0
        case VK_NUMPAD0: return KeyKind_KP0;
        case VK_NUMPAD1: return KeyKind_KP1;
        case VK_NUMPAD2: return KeyKind_KP2;
        case VK_NUMPAD3: return KeyKind_KP3;
        case VK_NUMPAD4: return KeyKind_KP4;
        case VK_NUMPAD5: return KeyKind_KP5;
        case VK_NUMPAD6: return KeyKind_KP6;
        case VK_NUMPAD7: return KeyKind_KP7;
        case VK_NUMPAD8: return KeyKind_KP8;
        case VK_NUMPAD9: return KeyKind_KP9;
        case VK_DECIMAL: return KeyKind_KPPeriod;
        case VK_DIVIDE:   return KeyKind_KPDivide;
        case VK_MULTIPLY: return KeyKind_KPMultiply;
        case VK_SUBTRACT: return KeyKind_KPMinus;
        case VK_ADD: return KeyKind_KPPlus;
        //case : return KeyKind_KPEnter;
        //case : return KeyKind_KPEquals;
        #endif

        case VK_UP: return KeyKind_Up;
        case VK_DOWN: return KeyKind_Down;
        case VK_RIGHT: return KeyKind_Right;
        case VK_LEFT: return KeyKind_Left;
        case VK_INSERT: return KeyKind_Insert;
        case VK_HOME: return KeyKind_Home;
        case VK_END: return KeyKind_End;
        case VK_PRIOR: return KeyKind_PageUp;
        case VK_NEXT: return KeyKind_PageDown;

        case VK_F1: return KeyKind_F1;
        case VK_F2: return KeyKind_F2;
        case VK_F3: return KeyKind_F3;
        case VK_F4: return KeyKind_F4;
        case VK_F5: return KeyKind_F5;
        case VK_F6: return KeyKind_F6;
        case VK_F7: return KeyKind_F7;
        case VK_F8: return KeyKind_F8;
        case VK_F9: return KeyKind_F9;
        case VK_F10: return KeyKind_F10;
        case VK_F11: return KeyKind_F11;
        case VK_F12: return KeyKind_F12;
        case VK_F13: return KeyKind_F13;
        case VK_F14: return KeyKind_F14;
        case VK_F15: return KeyKind_F15;

        case VK_NUMLOCK: return KeyKind_NumLock;
        case VK_OEM_ATTN: return KeyKind_CapsLock;
        case VK_SCROLL: return KeyKind_ScrolLock;
        case VK_RSHIFT: return KeyKind_Shift;
        case VK_LSHIFT: return KeyKind_Shift;
        case VK_LCONTROL: return KeyKind_Ctrl;
        case VK_RCONTROL: return KeyKind_Ctrl;
        case VK_MENU: return KeyKind_Alt;

        default:
            return KeyKind_TERMINATE;
    }
}

void tUpdateMouseBtn(MouseUpdateData& aData, WPARAM aWParam)
{
    aData.hold.set(MouseBtnKind_L, (aWParam & MK_LBUTTON) != 0);
    aData.hold.set(MouseBtnKind_R, (aWParam & MK_RBUTTON) != 0);
    aData.hold.set(MouseBtnKind_M, (aWParam & MK_MBUTTON) != 0);
}

} // namespace

//------------------------------------------------------------------------------
int Display::screenCount()const
{
    return 1;
}

//------------------------------------------------------------------------------
Screen& Display::screenAtIndex(const int aIndex)
{
    XBASE_ASSERT_LESS(aIndex, screenCount());
    XBASE_UNUSED(aIndex);
    return mainScreen();
}

//------------------------------------------------------------------------------
Screen& Display::mainScreen()
{
    return *mExt.mainScreen;
}

//------------------------------------------------------------------------------
void Display::show()
{
    mExt.isClosed = false;
    ShowWindow(mExt.window, SW_SHOWNORMAL);
    UpdateWindow(mExt.window);
}

//------------------------------------------------------------------------------
bool Display::isClosed()const
{
    return mExt.isClosed;
}

//------------------------------------------------------------------------------
Display_Ext::Display_Ext(const DisplayContext& aContext)
: window()
, windowClass()
, message()
, mainScreen()
, hidPtr()
, isClosed(true)
, keyboardUpdateData()
, mouseUpdateData()
{
    // インスタンスの取得
    HINSTANCE hinstance = (HINSTANCE)GetModuleHandle(0);

    // Windowクラスのセットアップ
    windowClass.cbSize = sizeof(windowClass);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProcess;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hinstance;
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = L"Cross Framework Application";
    windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&windowClass);

    // 変数準備
    const int style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

    // 矩形の計算
    RECT rect = {0, 0, LONG(aContext.width()), LONG(aContext.height())};
    AdjustWindowRect(
        &rect,
        style,
        FALSE
        );

// ウィンドウの作成
    window = CreateWindow(
        L"Cross Framework Application",
        L"Window Title",
        style,
        aContext.locationX(),
        aContext.locationY(),
        rect.right - rect.left,
        rect.bottom - rect.top,
        0, // hWndParent
        0, // hMenu
        hinstance,
        0 // lpParam
        );

// メインスクリーンの作成
    mainScreen.init(Ref(*this), aContext.width(), aContext.height());
}

//------------------------------------------------------------------------------
void Display_Ext::pollEvent(Application&)
{
    // pulseをクリア
    keyboardUpdateData.pulse.clear();

    // マウスのposUpdatedをクリア
    mouseUpdateData.posUpdated = false;

    // 今のディスプレイを設定
    tCurrentDisplay.set(*this);

    // メッセージ解析
    while (PeekMessage(&message, window, 0, 0, PM_REMOVE) != 0) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    // 今のディスプレイを設定解除
    tCurrentDisplay.unset(*this);

    // マウスの座標変換
    if (mouseUpdateData.posUpdated) {
        mouseUpdateData.pos.y = s16(int(mainScreen->height()) - 1 - mouseUpdateData.pos.y);
    }

    // マウスのボタンが何か押されていたら強制的にposUpdatedを設定
    if (mouseUpdateData.hold.isAnyOn()) {
        mouseUpdateData.posUpdated = true;
    }

    // Hid更新
    if (hidPtr.isValid()) {
        hidPtr->ext_().keyboard.update(keyboardUpdateData);
        hidPtr->ext_().mouse.update(mouseUpdateData);
    }
}

//------------------------------------------------------------------------------
LRESULT Display_Ext::WindowProcess(HWND aHWND, UINT aMsg, WPARAM aWParam, LPARAM aLParam)
{
    return tCurrentDisplay->windowProcess(aHWND, aMsg, aWParam, aLParam);
}

//------------------------------------------------------------------------------
LRESULT Display_Ext::windowProcess(HWND aHWND, UINT aMsg, WPARAM aWParam, LPARAM aLParam)
{
    switch (aMsg) {
        case WM_SYSKEYDOWN:
            break;

        case WM_SYSKEYUP:
            break;

        case WM_KEYDOWN:
        {
            KeyKind k = tToKeyKind(aWParam);
            if (k < KeyKind_TERMINATE) {
                keyboardUpdateData.hold.set(k, true);
                keyboardUpdateData.pulse.set(k, true);
            }
        }
        break;

        case WM_KEYUP:
        {
            KeyKind k = tToKeyKind(aWParam);
            if (k < KeyKind_TERMINATE) {
                keyboardUpdateData.hold.set(k, false);
            }
        }
        break;

        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MOUSEMOVE:
        {
            switch (aMsg) {
                case WM_LBUTTONDOWN:
                case WM_MBUTTONDOWN:
                case WM_RBUTTONDOWN:
                {// ボタンが押された
                    // 更新する前にキャプチャー設定
                    if (mouseUpdateData.hold.isAllOff()) {
                        SetCapture(aHWND);
                    }

                    // 更新
                    tUpdateMouseBtn(mouseUpdateData, aWParam);
                }
                break;

                case WM_LBUTTONUP:
                case WM_MBUTTONUP:
                case WM_RBUTTONUP:
                {// ボタンが離された
                    // 更新
                    tUpdateMouseBtn(mouseUpdateData, aWParam);

                    // キャプチャー設定
                    if (mouseUpdateData.hold.isAllOff()) {
                        ReleaseCapture();
                    }
                }
                break;
                default:
                    break;
            }

            // 位置設定
            const s16 mx = reinterpret_cast<const s16*>(&aLParam)[0];
            const s16 my = reinterpret_cast<const s16*>(&aLParam)[1];
            mouseUpdateData.pos = ScreenPos(mx, my);
            mouseUpdateData.posUpdated = true;
        }
        break;

        case WM_DESTROY:
            isClosed = true;
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(aHWND, aMsg, aWParam, aLParam);
}

} // namespace
// EOF
