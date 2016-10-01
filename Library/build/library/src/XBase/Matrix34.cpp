/**
 * @file
 * @brief Matrix34.hppの実装を記述する。
 * @author akino
 */
#include <XBase/Matrix34.hpp>

//------------------------------------------------------------
#include <XBase/Angle.hpp>
#include <XBase/Console.hpp>
#include <XBase/Math.hpp>
#include <XBase/Quaternion.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/Vector3.hpp>
#include <XBase/Matrix44.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
const Matrix34POD Matrix34POD::Identity()
{
    // よく使うことになるのでstaticデータとして使い初期化は１回だけにする。
    static Matrix34POD obj =
    {
        1,0,0, 0,1,0, 0,0,1, 0,0,0
    };
    return obj;
}

//------------------------------------------------------------
const Matrix34POD Matrix34POD::Translate(
    const f32 aX
    , const f32 aY
    , const f32 aZ
    )
{
    return Matrix34(
        1,0,0,aX
        ,0,1,0,aY
        ,0,0,1,aZ
        );
}

//------------------------------------------------------------
const Matrix34POD Matrix34POD::Translate(
    const Vector3POD& aVec
    )
{
    return Translate( aVec.x , aVec.y , aVec.z );
}

//------------------------------------------------------------
const Matrix34POD Matrix34POD::Scale(
    const f32 aX
    , const f32 aY
    , const f32 aZ
    )
{
    return Matrix34(
        aX,0,0,0
        ,0,aY,0,0
        ,0,0,aZ,0
        );
}

//------------------------------------------------------------
const Matrix34POD Matrix34POD::Scale(
    const Vector3POD& aVec
    )
{
    return Scale( aVec.x , aVec.y , aVec.z );
}

//------------------------------------------------------------
const Matrix34POD Matrix34POD::Rotate(
    const Angle& aAngle
    , const f32 aAxisX
    , const f32 aAxisY
    , const f32 aAxisZ
    )
{
    const f32 c = Math::CosF32( aAngle );
    const f32 s = Math::SinF32( aAngle );
    const f32 inv_c = 1.0f-c;
    const f32 x = aAxisX;
    const f32 y = aAxisY;
    const f32 z = aAxisZ;
    const f32 xy = x*y;
    const f32 xz = x*z;
    const f32 yz = y*z;
    const f32 xs = x*s;
    const f32 ys = y*s;
    const f32 zs = z*s;

    return Matrix34(
        x*x*inv_c+c , xy*inv_c-zs , xz*inv_c+ys , 0
        , xy*inv_c+zs , y*y*inv_c+c , yz*inv_c-xs , 0
        , xz*inv_c-ys , yz*inv_c+xs , z*z*inv_c+c , 0
        );
}

//------------------------------------------------------------
const Matrix34POD Matrix34POD::Rotate(
    const Angle& aAngle
    , const Vector3POD& aAxisVec
    )
{
    return Rotate( aAngle , aAxisVec.x , aAxisVec.y , aAxisVec.z );
}

//------------------------------------------------------------
const Matrix34POD Matrix34POD::LookAt(
    const Vector3POD& aEyePos
    , const Vector3POD& aTargetPos
    , const Vector3POD& aUpVec
    )
{
    // toTargetUnit
    Vector3 toTarget = aTargetPos - aEyePos;
    if ( toTarget.isZeroStrict() )
    {
        XBASE_NOT_REACH_ASSERT();
        toTarget = Vector3POD::UnitZ(); // fail safe code
    }
    const Vector3 toTargetUnit = toTarget.unit();

    // upVecUnit
    Vector3POD upVecUnit;
    if ( aUpVec.isZeroStrict() )
    {
        XBASE_INVALID_VALUE_ERROR( aUpVec );
        upVecUnit = Vector3::UnitY(); // fail safe code
    }
    else
    {
        upVecUnit = aUpVec.unit();
    }

    // toTarget以外の軸を再作成
    const Vector3POD s = toTargetUnit.cross( upVecUnit ).unit();
    const Vector3POD u = s.cross( toTargetUnit ).unit();
    Matrix34 mtx( s , u , -toTargetUnit , Vector3POD::Zero() );

    // 平行移動
    const Vector3POD invEyePos = -aEyePos;
    mtx.v[IndexWX] = invEyePos.dot( mtx.x() );
    mtx.v[IndexWY] = invEyePos.dot( mtx.y() );
    mtx.v[IndexWZ] = invEyePos.dot( mtx.z() );

    // 結果を返す
    return mtx;
}

//------------------------------------------------------------
const Vector3POD Matrix34POD::x()const
{
    return Vector3(
        v[IndexXX]
        , v[IndexXY]
        , v[IndexXZ]
        );
}

//------------------------------------------------------------
const Vector3POD Matrix34POD::y()const
{
    return Vector3(
        v[IndexYX]
        , v[IndexYY]
        , v[IndexYZ]
        );
}

//------------------------------------------------------------
const Vector3POD Matrix34POD::z()const
{
    return Vector3(
        v[IndexZX]
        , v[IndexZY]
        , v[IndexZZ]
        );
}

//------------------------------------------------------------
const Vector3POD Matrix34POD::w()const
{
    return Vector3(
        v[IndexWX]
        , v[IndexWY]
        , v[IndexWZ]
        );
}

//------------------------------------------------------------
void Matrix34POD::setX( const Vector3POD& aVal )
{
    v[IndexXX] = aVal.x;
    v[IndexXY] = aVal.y;
    v[IndexXZ] = aVal.z;
}

//------------------------------------------------------------
void Matrix34POD::setY( const Vector3POD& aVal )
{
    v[IndexYX] = aVal.x;
    v[IndexYY] = aVal.y;
    v[IndexYZ] = aVal.z;
}

//------------------------------------------------------------
void Matrix34POD::setZ( const Vector3POD& aVal )
{
    v[IndexZX] = aVal.x;
    v[IndexZY] = aVal.y;
    v[IndexZZ] = aVal.z;
}

//------------------------------------------------------------
void Matrix34POD::setW( const Vector3POD& aVal )
{
    v[IndexWX] = aVal.x;
    v[IndexWY] = aVal.y;
    v[IndexWZ] = aVal.z;
}

//------------------------------------------------------------
const Vector3POD Matrix34POD::mul( const Vector3POD& aVec )const
{
    return Vector3(
        aVec.x * v[IndexXX] + aVec.y * v[IndexYX] + aVec.z * v[IndexZX] + v[IndexWX]
        , aVec.x * v[IndexXY] + aVec.y * v[IndexYY] + aVec.z * v[IndexZY] + v[IndexWY]
        , aVec.x * v[IndexXZ] + aVec.y * v[IndexYZ] + aVec.z * v[IndexZZ] + v[IndexWZ]
        );
}

//------------------------------------------------------------
const Matrix34POD Matrix34POD::mul( const Matrix34POD& aRHS )const
{
    Matrix34POD mtx;

    // c0
    mtx.v[Index00] = 
        this->v[Index00] * aRHS.v[Index00] 
        + this->v[Index01] * aRHS.v[Index10] 
        + this->v[Index02] * aRHS.v[Index20]; 
    mtx.v[Index01] = 
        this->v[Index00] * aRHS.v[Index01] 
        + this->v[Index01] * aRHS.v[Index11] 
        + this->v[Index02] * aRHS.v[Index21]; 
    mtx.v[Index02] =
        this->v[Index00] * aRHS.v[Index02] 
        + this->v[Index01] * aRHS.v[Index12] 
        + this->v[Index02] * aRHS.v[Index22]; 
    mtx.v[Index03] =
        this->v[Index00] * aRHS.v[Index03] 
        + this->v[Index01] * aRHS.v[Index13] 
        + this->v[Index02] * aRHS.v[Index23] 
        + this->v[Index03];
    
    // c1
    mtx.v[Index10] =
        this->v[Index10] * aRHS.v[Index00] 
        + this->v[Index11] * aRHS.v[Index10] 
        + this->v[Index12] * aRHS.v[Index20]; 
    mtx.v[Index11] =
        this->v[Index10] * aRHS.v[Index01] 
        + this->v[Index11] * aRHS.v[Index11] 
        + this->v[Index12] * aRHS.v[Index21]; 
    mtx.v[Index12] =
        this->v[Index10] * aRHS.v[Index02] 
        + this->v[Index11] * aRHS.v[Index12] 
        + this->v[Index12] * aRHS.v[Index22]; 
    mtx.v[Index13] =
        this->v[Index10] * aRHS.v[Index03] 
        + this->v[Index11] * aRHS.v[Index13] 
        + this->v[Index12] * aRHS.v[Index23] 
        + this->v[Index13]; 
    
    // c2
    mtx.v[Index20] =
        this->v[Index20] * aRHS.v[Index00] 
        + this->v[Index21] * aRHS.v[Index10] 
        + this->v[Index22] * aRHS.v[Index20]; 
    mtx.v[Index21] =
        this->v[Index20] * aRHS.v[Index01] 
        + this->v[Index21] * aRHS.v[Index11] 
        + this->v[Index22] * aRHS.v[Index21]; 
    mtx.v[Index22] =
        this->v[Index20] * aRHS.v[Index02] 
        + this->v[Index21] * aRHS.v[Index12] 
        + this->v[Index22] * aRHS.v[Index22]; 
    mtx.v[Index23] =
        this->v[Index20] * aRHS.v[Index03] 
        + this->v[Index21] * aRHS.v[Index13] 
        + this->v[Index22] * aRHS.v[Index23] 
        + this->v[Index23]; 
    
    return mtx;
}

//------------------------------------------------------------
Matrix34POD& Matrix34POD::mulAssign( const Matrix34POD& aRHS )
{
    *this = mul( aRHS );
    return *this;
}

//------------------------------------------------------------
const Vector3POD Matrix34POD::operator*( const Vector3POD& aRHS )const
{
    return mul( aRHS );    
}

//------------------------------------------------------------
const Matrix34POD Matrix34POD::operator*( const Matrix34POD& aRHS )const
{
    return mul( aRHS );    
}

//------------------------------------------------------------
Matrix34POD& Matrix34POD::operator*=( const Matrix34POD& aRHS )
{
    mulAssign( aRHS );
    return *this;
}

//------------------------------------------------------------
const Matrix34POD Matrix34POD::invert()const
{
    const float c = 0.0f
        + v[Index00] * v[Index11] * v[Index22]
        + v[Index01] * v[Index12] * v[Index20]
        + v[Index02] * v[Index10] * v[Index21] 
        - v[Index00] * v[Index12] * v[Index21] 
        - v[Index01] * v[Index10] * v[Index22] 
        - v[Index02] * v[Index11] * v[Index20];

    if ( c == 0.0f )
    {
        XBASE_NOT_REACH_ASSERT();
        return Identity();
    }

    Matrix34POD b;
    b.v[Index00] 
        = v[Index11] * v[Index22] + v[Index12] * v[Index23] * 0 + v[Index13] * v[Index21] * 0
        - v[Index11] * v[Index23] * 0 - v[Index12] * v[Index21] - v[Index13] * v[Index22] * 0;
    b.v[Index01] 
        = v[Index01] * v[Index23] * 0 + v[Index02] * v[Index21] + v[Index03] * v[Index22] * 0
        - v[Index01] * v[Index22] - v[Index02] * v[Index23] * 0 - v[Index03] * v[Index21] * 0;
    b.v[Index02] 
        = v[Index01] * v[Index12] + v[Index02] * v[Index13] * 0 + v[Index03] * v[Index11] * 0
        - v[Index01] * v[Index13] * 0 - v[Index02] * v[Index11] - v[Index03] * v[Index12] * 0;
    b.v[Index03]
        = v[Index01] * v[Index13] * v[Index22] + v[Index02] * v[Index11] * v[Index23] + v[Index03] * v[Index12] * v[Index21]
        - v[Index01] * v[Index12] * v[Index23] - v[Index02] * v[Index13] * v[Index21] - v[Index03] * v[Index11] * v[Index22];
    b.v[Index10]
        = v[Index10] * v[Index23] * 0 + v[Index12] * v[Index20] + v[Index13] * v[Index22] * 0
        - v[Index10] * v[Index22] - v[Index12] * v[Index23] * 0 - v[Index13] * v[Index20] * 0;
    b.v[Index11]
        = v[Index00] * v[Index22] + v[Index02] * v[Index23] * 0 + v[Index03] * v[Index20] * 0
        - v[Index00] * v[Index23] * 0 - v[Index02] * v[Index20] - v[Index03] * v[Index22] * 0;
    b.v[Index12]
        = v[Index00] * v[Index13] * 0 + v[Index02] * v[Index10] + v[Index03] * v[Index12] * 0
        - v[Index00] * v[Index12] - v[Index02] * v[Index13] * 0 - v[Index03] * v[Index10] * 0;
    b.v[Index13]
        = v[Index00] * v[Index12] * v[Index23] + v[Index02] * v[Index13] * v[Index20] + v[Index03] * v[Index10] * v[Index22]
        - v[Index00] * v[Index13] * v[Index22] - v[Index02] * v[Index10] * v[Index23] - v[Index03] * v[Index12] * v[Index20];
    b.v[Index20] 
        = v[Index10] * v[Index21] + v[Index11] * v[Index23] * 0 + v[Index13] * v[Index20] * 0
        - v[Index10] * v[Index23] * 0 - v[Index11] * v[Index20] - v[Index13] * v[Index21] * 0;
    b.v[Index21] 
        = v[Index00] * v[Index23] * 0 + v[Index01] * v[Index20] + v[Index03] * v[Index21] * 0
        - v[Index00] * v[Index21] - v[Index01] * v[Index23] * 0 - v[Index03] * v[Index20] * 0;
    b.v[Index22]
        = v[Index00] * v[Index11] + v[Index01] * v[Index13] * 0 + v[Index03] * v[Index10] * 0
        - v[Index00] * v[Index13] * 0 - v[Index01] * v[Index10] - v[Index03] * v[Index11] * 0;
    b.v[Index23]
        = v[Index00] * v[Index13] * v[Index21] + v[Index01] * v[Index10] * v[Index23] + v[Index03] * v[Index11] * v[Index20]
        - v[Index00] * v[Index11] * v[Index23] - v[Index01] * v[Index13] * v[Index20] - v[Index03] * v[Index10] * v[Index21];

    b.v[Index00] /= c;
    b.v[Index01] /= c;
    b.v[Index02] /= c;
    b.v[Index03] /= c;
    b.v[Index10] /= c;
    b.v[Index11] /= c;
    b.v[Index12] /= c;
    b.v[Index13] /= c;
    b.v[Index20] /= c;
    b.v[Index21] /= c;
    b.v[Index22] /= c;
    b.v[Index23] /= c;

    return b;
}

//------------------------------------------------------------
const Quaternion Matrix34POD::toQuaternion()const
{ 
    Quaternion q;
    
    {
        const float tr = v[Index00] + v[Index11] + v[Index22] + 1.0f;
        if ( 1.0f <= tr ) 
        {
            float s = 0.5f / Math::SqrtF32(tr);
            q.w= 0.25f / s;
            q.x= (v[Index21] - v[Index12]) * s;
            q.y= (v[Index02] - v[Index20]) * s;
            q.z= (v[Index10] - v[Index01]) * s;
            return q;
        }
    }

    const float maxVal = v[Index22] < v[Index11]
        ? v[Index11]
        : v[Index22]
        ;
    if ( maxVal < v[Index00] ) 
    {
        float s = Math::SqrtF32(v[Index00] - (v[Index11] + v[Index22]) + 1.0f);
        const float x = s * 0.5f;
        s = 0.5f / s;
        q.x= x;
        q.y= (v[Index10] + v[Index01]) * s;
        q.z= (v[Index02] + v[Index20]) * s;
        q.w= (v[Index21] - v[Index12]) * s;
        return q;
    }
    else if ( maxVal == v[Index11] )
    {
        float s = Math::SqrtF32(v[Index11] - (v[Index22] + v[Index00]) + 1.0f);
        const float y = s * 0.5f;
        s = 0.5f / s;
        q.x= (v[Index10] + v[Index01]) * s;
        q.y= y;
        q.z= (v[Index21] + v[Index12]) * s;
        q.w= (v[Index02] - v[Index20]) * s;
        return q;
    }
    else
    {
        float s = Math::SqrtF32(v[Index22] - (v[Index00] + v[Index11]) + 1.0f);
        const float z = s * 0.5f;
        s = 0.5f / s;
        q.x= (v[Index02] + v[Index20]) * s;
        q.y= (v[Index21] + v[Index12]) * s;
        q.z= z;
        q.w= (v[Index10] - v[Index01]) * s;
        return q;
    }
}

//------------------------------------------------------------
const Matrix44POD Matrix34POD::toMatrix44()const
{
    return Matrix44(
        v[Index00] , v[Index01],  v[Index02] , v[Index03]
        ,v[Index10] , v[Index11],  v[Index12] , v[Index13]
        ,v[Index20] , v[Index21],  v[Index22] , v[Index23]
        ,0 , 0,  0 , 1
        );
}

//------------------------------------------------------------
void Matrix34POD::dump()const
{
    XBASE_COUTFMT( "Matrix34POD::dump %p\n" , this );
    XBASE_COUTFMT( "( %f , %f , %f , %f )\n" , v[Index00] , v[Index01] , v[Index02] , v[Index03] );
    XBASE_COUTFMT( "( %f , %f , %f , %f )\n" , v[Index10] , v[Index11] , v[Index12] , v[Index13] );
    XBASE_COUTFMT( "( %f , %f , %f , %f )\n" , v[Index20] , v[Index21] , v[Index22] , v[Index23] );
}

//------------------------------------------------------------
Matrix34::Matrix34()
: Matrix34POD( Identity() )
{
}

//------------------------------------------------------------
Matrix34::Matrix34( const Matrix34POD& aObj )
: Matrix34POD( aObj )
{
}

//------------------------------------------------------------
Matrix34::Matrix34(
    const f32 aR0C0 , const f32 aR0C1 , const f32 aR0C2 , const f32 aR0C3
    , const f32 aR1C0 , const f32 aR1C1 , const f32 aR1C2 , const f32 aR1C3
    , const f32 aR2C0 , const f32 aR2C1 , const f32 aR2C2 , const f32 aR2C3
    )
{
    v[Index00] = aR0C0;
    v[Index10] = aR1C0;
    v[Index20] = aR2C0;
    v[Index01] = aR0C1;
    v[Index11] = aR1C1;
    v[Index21] = aR2C1;
    v[Index02] = aR0C2;
    v[Index12] = aR1C2;
    v[Index22] = aR2C2;
    v[Index03] = aR0C3;
    v[Index13] = aR1C3;
    v[Index23] = aR2C3;
}

//------------------------------------------------------------
Matrix34::Matrix34( 
    const Vector3POD& aX
    , const Vector3POD& aY
    , const Vector3POD& aZ
    , const Vector3POD& aW
    )
{
    setX( aX );
    setY( aY );
    setZ( aZ );
    setW( aW );
}

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
