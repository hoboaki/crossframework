/**
 * @file
 * @brief NonCopyable型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_NONCOPYABLE_HPP)
#else
#define XBASE_INCLUDED_NONCOPYABLE_HPP

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Util
//@{
    /**
     * @brief 誤ってコピーできないようにする継承専用クラス。
     * @code
// 例
class Hoge : private NonCopyable
{
};
Hoge a;
Hoge b = a; // コピーできないのでコンパイルエラー。
     * @endcode
     */
    class NonCopyable
    {
    protected:
        NonCopyable(){}
    private:
        NonCopyable( const NonCopyable& );
        void operator=( const NonCopyable& );
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
