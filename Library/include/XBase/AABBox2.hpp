/**
 * @file
 * @brief AABBox2型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_AABBOX2_HPP)
#else
#define XBASE_INCLUDED_AABBOX2_HPP

//------------------------------------------------------------
#include <XBase/Vector2.hpp>

//------------------------------------------------------------
namespace XBase {
    class AABBox2i;
}

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /**
     * @brief 浮動小数型2次元AABB(Axis Aligned Bounding Box)。
     * @details
     * 四則演算のadd( AABB ),mul( scale )は２つのAABBの補間を実現するために実装しています。@n
     */
    class AABBox2
    {
    public:
        //------------------------------------------------------------
        /// @name コンストラクタ
        //@{
        AABBox2(); ///< AABBox2( Vector2::Zero() ) で作成。
        AABBox2( const Vector2POD& aPos ); ///< 1点を含むAABBを作成。
        AABBox2( const Vector2POD& aPos1 , const Vector2POD& aPos2 ); ///< 2点を含むAABBを作成。
        //@}
        
        //------------------------------------------------------------
        /// @name 点の取得
        //@{
        const Vector2POD min()const;    ///< AABBの小さい方の点を取得。
        const Vector2POD max()const;    ///< AABBの大きい方の点を取得。
        const Vector2POD center()const; ///< AABBの中心点を取得。
        const Vector2POD posLB()const; ///< Vector2( left()  , bottom() )を取得。
        const Vector2POD posRB()const; ///< Vector2( right() , bottom() )を取得。
        const Vector2POD posLT()const; ///< Vector2( left()  , top() )を取得。
        const Vector2POD posRT()const; ///< Vector2( right() , top() )を取得。
        float left()const;   ///< min().xを取得。
        float right()const;  ///< max().xを取得。
        float bottom()const; ///< min().yを取得。
        float top()const;    ///< max().yを取得。
        //@}

        //------------------------------------------------------------
        /// @name 大きさの取得
        //@{
        float width()const;  ///< xの幅を取得。
        float height()const; ///< yの幅を取得。
        const Vector2POD size()const;     ///< Vector2( width() , height() ) を取得。
        const Vector2POD halfSize()const; ///< size() * 0.5f を取得。
        //@}

        //------------------------------------------------------------
        /// @name 結合。
        //@{
        const AABBox2 merge( const Vector2POD& aPos )const; ///< 自分自身と指定の点を含むAABBを取得。
        const AABBox2 merge( const AABBox2& aAABB )const; ///< 自分自身と指定のAABBを含むAABBを取得。
        void mergeAssign( const Vector2POD& aPos ); ///< 自分自身と指定の点を含むAABBに設定する。
        void mergeAssign( const AABBox2& aAABB ); ///< 自分自身と指定のAABBを含むAABBに設定する。
        //@}

        //------------------------------------------------------------
        /// @name 判定
        //@{
        /**
         * @brief 指定のAABBが重なっているか。
         * @details 
         * 同線上は重なっているとして判定します。
         */
        bool isIntersects( const AABBox2& aAABB )const;

        /**
         * @brief 指定の点を含んでいるか。
         * @details 
         * 線上は含んでいるとして判定します。
         */
        bool isContains( const Vector2POD& aPos )const;

        /**
         * @brief 指定のAABBを含んでいるか。
         * @details
         * 同線上は含んでいると判定しています。
         */
        bool isContains( const AABBox2& aAABB )const;
        //@}
        
        //------------------------------------------------------------
        /// @name 四則演算
        //@{
        const AABBox2 add( const Vector2POD& aTrans )const; ///< min() max() に値を加算した結果を取得する。
        const AABBox2 sub( const Vector2POD& aTrans )const; ///< min() max() から値を減算した結果を取得する。
        const AABBox2 add( const AABBox2& aAABB )const; ///< min() max() をそれぞれ加算した結果を取得する。
        const AABBox2 sub( const AABBox2& aAABB )const; ///< min() max() をそれぞれ減算した結果を取得する。
        const AABBox2 mul( f32 aScale )const; ///< min() max() に値を乗算した結果を取得する。
        void addAssign( const Vector2POD& aTrans ); ///< min() max() に値を加算する。
        void subAssign( const Vector2POD& aTrans ); ///< min() max() から値を減算する。
        void addAssign( const AABBox2& aAABB ); ///< min() max() をそれぞれ加算する。
        void subAssign( const AABBox2& aAABB ); ///< min() max() をそれぞれ減算する。
        void mulAssign( f32 aScale ); ///< min() max() に値を乗算する。
        //@}
        
        //------------------------------------------------------------
        /// @name 演算子オーバーロード
        //@{
        const AABBox2 operator+( const Vector2POD& )const; ///< add() 。
        const AABBox2 operator-( const Vector2POD& )const; ///< sub() 。
        const AABBox2 operator+( const AABBox2& )const; ///< add() 。
        const AABBox2 operator-( const AABBox2& )const; ///< sub() 。
        const AABBox2 operator*( f32 )const; ///< mul() 。
        AABBox2& operator+=( const Vector2POD& ); ///< addAssign() 。
        AABBox2& operator-=( const Vector2POD& ); ///< subAssign() 。
        AABBox2& operator+=( const AABBox2& ); ///< addAssign() 。
        AABBox2& operator-=( const AABBox2& ); ///< subAssign() 。
        AABBox2& operator*=( f32 ); ///< mulAssign() 。
        //@}

        //------------------------------------------------------------
        /// @name 変換
        //@{
        const AABBox2i toAABB2i()const; ///< 切り捨てたmin()、切り上げたmax()の値を使って整数版AABBに変換。
        //@}
    private:
        Vector2 mMin;
        Vector2 mMax;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
