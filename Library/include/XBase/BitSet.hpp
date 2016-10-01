// 文字コード：UTF-8
#if defined(XBASE_INCLUDED_BITSET_HPP)
#else
#define XBASE_INCLUDED_BITSET_HPP

//------------------------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Collection
//@{
    /// @brief ビットを扱うコレクション(POD版)。
    /// @details
    /// BIT_COUNTには扱うビット数を指定してください。 @n
    /// ALIGNMENTには要求するアライメント値を指定してください。 @n
    template < uint BIT_COUNT , uint ALIGNMENT = 4 >
    struct BitSetPOD
    {
        //============================================================
        // private
        enum  
        {
            ByteSizeRaw_ = ( BIT_COUNT + 7 ) / 8 ,
            ByteSize_    = ByteSizeRaw_ + ( ALIGNMENT - 1 ) / ALIGNMENT
        };
        byte_t bits_[ ByteSize_ ];
        
        //============================================================
        // public
        
        /// @name 型・定数
        //@{
        enum { BitCount = BIT_COUNT }; ///< ビット数。
        typedef BitSetPOD< BitCount > MyType; ///< 自分自身の型。
        //@}

        /// @name 全ビットの操作
        //@{
        /// 全ビットをfalseにする。
        void clear()
        {
            for ( uint i = 0; i < MyType::ByteSize_; ++i )
            {
                bits_[i] = 0;
            }
        }
        //@}

        /// @name 各ビットの設定・取得
        //@{
        /// 指定番目のビットの値を設定する。
        void set( uint aIndex , bool aFlag )
        {
            // チェック
            if ( BitCount <= aIndex )
            {
                XBASE_INVALID_VALUE_ERROR( aIndex );
                return;
            }

            // 設定
            byte_t& val = bits_[ aIndex >> 3 ];
            const byte_t mask = byte_t( 1 << ( aIndex & 0x7 ) );
            val = ( val & ~mask ) | ( aFlag ? mask : 0 );
        }

        /// 指定番目のビットをたてる。
        void on( uint aIndex )
        {
            set( aIndex , true );
        }
                
        /// 指定番目のビットをおろす。
        void off( uint aIndex )
        {
            set( aIndex , false );
        }

        /// 指定番目のビットの値を取得する。
        bool get( uint aIndex )const
        {
            // チェック
            if ( BitCount <= aIndex )
            {
                XBASE_INVALID_VALUE_ERROR( aIndex );
                return bool();
            }
            
            // 取得
            const byte_t& val = bits_[ aIndex >> 3 ];
            const byte_t mask = byte_t( 1 << ( aIndex & 0x7 ) );
            return ( val & mask ) != 0 ? true : false;
        }
        /// 1つ以上のビットがたっているか。
        bool isAnyOn()const
        {
            for ( uint i = 0; i < ByteSize_; ++i )
            {
                if ( bits_[i] != 0 )
                {
                    return true;
                }
            }
            return false;
        }
        /// 全てのビットがたっていない状態か。
        bool isAllOff()const
        {
            return !isAnyOn();
        }
        /// 全てのビットがたっている状態か。
        bool isAllOn()const
        {
            for ( uint i = 0; i < BitCount; ++i )
            {
                if ( !get( i ) )
                {
                    return false;
                }
            }
            return true;
        }
        //@}
        
        /// @name 演算
        //@{
        /// ビットを反転した値を取得。
        const MyType operator ~()const
        {
            MyType obj = *this;
            for ( uint i = 0; i < ByteSize_; ++i )
            {
                obj.bits_[ i ] = ~obj.bits_[ i ];
            }
            return obj;
        }
        
        /// 論理積を取得。
        const MyType operator &( const MyType& aRHS )const
        {
            MyType obj = *this;
            for ( uint i = 0; i < ByteSize_; ++i )
            {
                 obj.bits_[ i ] = bits_[i] & aRHS.bits_[i];
            }
            return obj;
        }
        
        /// 論理和を取得。
        const MyType operator |( const MyType& aRHS )const
        {
            MyType obj = *this;
            for ( uint i = 0; i < ByteSize_; ++i )
            {
                 obj.bits_[ i ] = bits_[i] | aRHS.bits_[i];
            }
            return obj;
        }
        
        /// 排他的論理和を取得。
        const MyType operator ^( const MyType& aRHS )const
        {
            MyType obj = *this;
            for ( uint i = 0; i < ByteSize_; ++i )
            {
                obj.bits_[ i ] = bits_[i] ^ aRHS.bits_[i];
            }
            return obj;
        }
        //@} 
    };

    /// BitSetPOD のクラス版。
    template < uint BIT_COUNT , uint ALIGNMENT = 4 >
    class BitSet : public BitSetPOD< BIT_COUNT , ALIGNMENT >
    {
    public:
        /// @name コンストラクタ
        //@{
        /// 全てoffの状態で作成。
        BitSet()
        {
            BitSetPOD< BIT_COUNT , ALIGNMENT >::clear();
        }

        /// コピーして作成。
        BitSet( const BitSetPOD< BIT_COUNT , ALIGNMENT >& aObj )
        {
            static_cast< BitSetPOD< BIT_COUNT , ALIGNMENT >& >( *this ) = aObj;
        }

        //@}
    };
//@}

} // namespace
#endif
// EOF
