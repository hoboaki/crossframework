using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// 3つのベクトルで姿勢を表す構造体。
    /// </summary>
    public struct Direction3
    {
        //------------------------------------------------------------
        /// <summary>
        /// 基本姿勢。
        /// </summary>
        static public Direction3 Identity
        {
            get
            {
                Direction3 d = new Direction3();
                d.Left.X = 1.0f;
                d.Up.Y = 1.0f;
                d.Front.Z = 1.0f;
                return d;
            }
        }

        //============================================================

        /// <summary>
        /// 左方向。
        /// </summary>
        public Vector3 Left;

        /// <summary>
        /// 上方向。
        /// </summary>
        public Vector3 Up;

        /// <summary>
        /// 前方向。
        /// </summary>
        public Vector3 Front;

        //============================================================

        //------------------------------------------------------------
        /// <summary>
        /// クォータニオンに変換。
        /// </summary>
        /// <returns></returns>
        public Quaternion ToQuaternion()
        {
            Quaternion q;
    
            {
                float tr = Left.X + Up.Y + Front.Z + 1.0f;
                if ( 1.0f <= tr ) 
                {
                    float s = 0.5f / (float)Math.Sqrt(tr);
                    q.W= 0.25f / s;
                    q.X= (Up.Z - Front.Y) * s;
                    q.Y= (Front.X - Left.Z) * s;
                    q.Z= (Left.Y - Up.X) * s;
                    return q;
                }
            }

            float maxVal = Front.Z < Up.Y
                ? Up.Y
                : Front.Z
                ;
            if ( maxVal < Left.X ) 
            {
                float s = (float)Math.Sqrt(Left.X - (Up.Y + Front.Z) + 1.0f);
                float x = s * 0.5f;
                s = 0.5f / s;
                q.X= x;
                q.Y= (Left.Y + Up.X) * s;
                q.Z= (Front.X + Left.Z) * s;
                q.W= (Up.Z - Front.Y) * s;
                return q;
            }
            else if ( maxVal == Up.Y )
            {
                float s = (float)Math.Sqrt(Up.Y - (Front.Z + Left.X) + 1.0f);
                float y = s * 0.5f;
                s = 0.5f / s;
                q.X= (Left.Y + Up.X) * s;
                q.Y= y;
                q.Z= (Up.Z + Front.Y) * s;
                q.W= (Front.X - Left.Z) * s;
                return q;
            }
            else
            {
                float s = (float)Math.Sqrt(Front.Z - (Left.X + Up.Y) + 1.0f);
                float z = s * 0.5f;
                s = 0.5f / s;
                q.X= (Front.X + Left.Z) * s;
                q.Y= (Up.Z + Front.Y) * s;
                q.Z= z;
                q.W= (Left.Y - Up.X) * s;
                return q;
            }
        }
    }
}
