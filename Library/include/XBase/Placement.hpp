/**
 * @file
 * @brief Placement型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_PLACEMENT_HPP)
#else
#define XBASE_INCLUDED_PLACEMENT_HPP

//------------------------------------------------------------
#include <new>
#include <XBase/BuiltInTypes.hpp>
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Util
//@{
    /**
     * @brief 確保済みのメモリ領域からオブジェクトを生成するためのテンプレートクラス。
     * @details
     * クラスメンバの初期化子で生成できないメンバ変数を後から初期化するときに使います。@n
     * @n
     * init 関数の引数に参照を渡す場合は Ref() を使うことをおすすめします。@n
     * Ref() を使わない場合はオブジェクトのコピーが走るので注意してください。 @n
     * @code
// 例
::XBase::Placement< ::XBase::Vector3 > vec3;
vec3.init( 1 , 2 , 3 );
const float len = vec3->length();
     * @endcode
     */
    template< typename T >
    class Placement
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        Placement() : mPtr( 0 ) {}
        ~Placement() { reset(); }
        //@}

        /// @name アクセス
        //@{
        /// 生成済みか。
        bool isValid()const { return mPtr != 0; }

        /// 生成済みのオブジェクトのポインタを取得する。
        T*   ptr()const { XBASE_POINTER_ASSERT( mPtr ); return mPtr; }

        /// 生成済みのオブジェクトの参照を取得する。
        T&   ref()const { return *ptr(); }
        //@}

        /// @name 演算子オーバーロード
        //@{
        T* operator->()const { return ptr(); } ///< ptr() のエイリアス。
        T& operator*()const  { return ref(); } ///< ref() のエイリアス。
        //@}

        /// @name 破棄
        //@{
        /// 生成済みなら破棄する。
        void reset()
        {
            if ( isValid() )
            {
                mPtr->~T();
                mPtr = 0;
            }
        }
        //@}

        /// @name 生成
        //@{
        void init()
        {
            prepareCtor();
            new ( mPtr ) T();
        }
        template< typename A0 >
        void init( A0 a0 )
        {
            prepareCtor();
            new( mPtr ) T( a0 );
        }
        template< typename A0 , typename A1 >
        void init( A0 a0 , A1 a1 )
        {
            prepareCtor();
            new ( mPtr ) T( a0 , a1 );
        }
        template< typename A0 , typename A1 , typename A2 >
        void init( A0 a0 , A1 a1 , A2 a2 )
        {
            prepareCtor();
            new ( mPtr ) T( a0 , a1 , a2 );
        }
        template< typename A0 , typename A1 , typename A2 , typename A3 >
        void init( A0 a0 , A1 a1 , A2 a2 , A3 a3 )
        {
            prepareCtor();
            new ( mPtr ) T( a0 , a1 , a2 , a3 );
        }
        template< typename A0 , typename A1 , typename A2 , typename A3 , typename A4 >
        void init( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 )
        {
            prepareCtor();
            new ( mPtr ) T( a0 , a1 , a2 , a3 , a4 );
        }
        template< typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 >
        void init( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 )
        {
            prepareCtor();
            new ( mPtr ) T( a0 , a1 , a2 , a3 , a4 , a5 );
        }
        template< typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 >
        void init( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 )
        {
            prepareCtor();
            new ( mPtr ) T( a0 , a1 , a2 , a3 , a4 , a5 , a6 );
        }
        template< typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 >
        void init( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 )
        {
            prepareCtor();
            new ( mPtr ) T( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 );
        }
        template< typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 >
        void init( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 )
        {
            prepareCtor();
            new ( mPtr ) T( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 );
        }
        template< typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 >
        void init( A0 a0 , A1 a1 , A2 a2 , A3 a3 , A4 a4 , A5 a5 , A6 a6 , A7 a7 , A8 a8 , A9 a9 )
        {
            prepareCtor();
            new ( mPtr ) T( a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 );
        }
        //@}

    private:
        T*     mPtr;
        byte_t mBytes[ sizeof(T) ];
        //------------------------------------------------------------
        void prepareCtor()
        {
            reset();
            mPtr = reinterpret_cast< T* >( mBytes );
        }
    };

//@}
}
//------------------------------------------------------------
#endif
// EOF
