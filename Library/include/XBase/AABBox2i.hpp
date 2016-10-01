// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_AABBOX2I_HPP)
#else
#define XBASE_INCLUDED_AABBOX2I_HPP

//------------------------------------------------------------------------------
#include <XBase/Vector2i.hpp>

//------------------------------------------------------------------------------
namespace XBase {
    class AABBox2;
}

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Math
//@{
    /// @brief 整数型2次元AABB(Axis Aligned Bounding Box)。
    /// @details
    /// float版のAABBとは領域の示し方が異なるので注意してください。@n
    /// float版は min() と max() で表現していますが、
    /// int版は begin() と end() で表現しています。@n
    /// また、float版とは異なり end() 上の点は範囲内とは判定しません。@n
    /// @n
    /// このようなルールを設けるため、AABB内の各セルの処理について次のようなfor分を書くことを想定しています。@n
    /// 経験上、整数版のAABBはこのほうが使い勝手がよいと作者は考えています。@n
    /// @code
    /// void func( const AABBox2i& aAABB )
    /// {
    ///     for ( int y = aAABB.begin().y; t < aAABB.end().y; ++y )
    ///     {
    ///         for ( int x = aAABB.begin().x; t < aAABB.end().x; ++x )
    ///         {
    ///         }
    ///     }
    /// }
    /// @endcode
    class AABBox2i
    {
    public:
        //------------------------------------------------------------------------------
        /// @name 定数
        //@{
        static const AABBox2i Largest(); ///< 全てを包むAABB。
        //@}

        //------------------------------------------------------------------------------
        /// @name コンストラクタ
        //@{
        AABBox2i(); ///< AABBox2i( Vector2i::Zero() ) で作成。
        AABBox2i( const Vector2iPOD& aBegin ); ///< AABBox2i( aPos , 0 , 0 ) で作成。
        AABBox2i( const Vector2iPOD& aBegin , uint aWidth , uint aHeight ); ///< 基準となる点とサイズを指定してAABBを作成。
        //@}
        
        //------------------------------------------------------------------------------
        /// @name 点の取得
        //@{
        const Vector2iPOD begin()const; ///< AABBの基準点を取得。
        const Vector2iPOD end()const;   ///< AABBの端点を取得。
        const Vector2iPOD min()const;  ///< begin() のエイリアス。
        const Vector2iPOD term()const; ///< end() のエイリアス。
        //@}

        //------------------------------------------------------------------------------
        /// @name 大きさの取得
        //@{
        uint width()const;  ///< xの幅を取得。
        uint height()const; ///< yの幅を取得。
        //@}
        
        //------------------------------------------------------------------------------
        /// @name 正領域
        //@{
        bool isPositive()const; ///< begin() が (0,0) 以上か。
        const AABBox2i toPositive()const; ///< begin() が (0,0) 未満なら (0,0) 以上になるようにしたAABBを取得する。
        //@}

        //------------------------------------------------------------------------------
        /// @name 結合
        //@{
        const AABBox2i merge( const AABBox2i& aAABB )const; ///< 自分自身と指定のAABBを含むAABBを取得。
        void mergeAssign( const AABBox2i& aAABB ); ///< 自分自身と指定のAABBを含むAABBに設定する。
        //@}
        
        //------------------------------------------------------------------------------
        /// @name 判定
        //@{
        /// @brief 指定のAABBが重なっているか。
        /// @details 
        /// term() 線上は重なっていないとして判定します。
        bool isIntersects( const AABBox2i& aAABB )const;

        /// @brief 指定の点を含んでいるか。
        /// @return begin() <= aPos && aPos() < end()
        bool isContains( const Vector2iPOD& aPos )const;

        /// @brief 指定のAABBを含んでいるか。
        /// @details
        /// term() 線上は重なっていないとして判定します。
        bool isContains( const AABBox2i& aAABB )const;
        //@}
        
        //------------------------------------------------------------------------------
        /// @name 四則演算
        //@{
        const AABBox2i add( const Vector2iPOD& aTrans )const; ///< min() term() に値を加算した結果を取得する。
        const AABBox2i sub( const Vector2iPOD& aTrans )const; ///< min() term() から値を減算した結果を取得する。
        void addAssign( const Vector2iPOD& aTrans ); ///< min() term() に値を加算する。
        void subAssign( const Vector2iPOD& aTrans ); ///< min() term() から値を減算する。
        //@}
        
        //------------------------------------------------------------------------------
        /// @name 演算子オーバーロード
        //@{
        const AABBox2i operator+( const Vector2iPOD& )const; ///< add() 。
        const AABBox2i operator-( const Vector2iPOD& )const; ///< sub() 。
        AABBox2i& operator+=( const Vector2iPOD& ); ///< addAssign() 。
        AABBox2i& operator-=( const Vector2iPOD& ); ///< subAssign() 。
        //@}

        //------------------------------------------------------------------------------
        /// @name 変換
        //@{
        const AABBox2 toAABB2f()const; ///< AABBox2( min() , term() ) に変換。
        //@}

    private:
        Vector2i mMin;
        Vector2i mTerm;
    };
//@}

} // namespace
#endif
// EOF
