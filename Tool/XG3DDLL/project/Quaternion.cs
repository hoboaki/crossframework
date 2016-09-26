using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// クォータニオン。
    /// </summary>
    public struct Quaternion
    {
        /// <summary>
        /// x値。
        /// </summary>
        public float X;

        /// <summary>
        /// y値。
        /// </summary>
        public float Y;

        /// <summary>
        /// z値。
        /// </summary>
        public float Z;

        /// <summary>
        /// w値。
        /// </summary>
        public float W;

        //============================================================

        /// <summary>
        /// XMLから読み込む。
        /// </summary>
        /// <param name="aXml"></param>
        /// <returns></returns>
        public static Quaternion FromXml(XmlNode aXml)
        {
            Quaternion obj = new Quaternion();
            obj.X = float.Parse(aXml.Attributes["x"].Value);
            obj.Y = float.Parse(aXml.Attributes["y"].Value);
            obj.Z = float.Parse(aXml.Attributes["z"].Value);
            obj.W = float.Parse(aXml.Attributes["w"].Value);
            return obj;
        }

        //============================================================

        //------------------------------------------------------------
        /// <summary>
        /// 回転行列に変換する。
        /// </summary>
        /// <returns></returns>
        public Direction3 ToDirection3()
        {
            float lenSrc = (float)Math.Sqrt( W*W + X*X + Y*Y + Z*Z ) ;
            if ( lenSrc == 0 )
            {
                return Direction3.Identity;
            }

            float len = 2.0f / (lenSrc*lenSrc);
            float x2 = X * X * len;
            float y2 = Y * Y * len;
            float z2 = Z * Z * len;
            float xy = X * Y * len;
            float yz = Y * Z * len;
            float zx = Z * X * len;
            float xw = X * W * len;
            float yw = Y * W * len;
            float zw = Z * W * len;
    
            Direction3 dir;
            dir.Left.X = 1.0f - y2 - z2;
            dir.Left.Y = xy + zw;
            dir.Left.Z = zx - yw;
            dir.Up.X = xy - zw;
            dir.Up.Y = 1.0f - z2 - x2;
            dir.Up.Z = yz + xw;
            dir.Front.X = zx + yw;
            dir.Front.Y = yz - xw;
            dir.Front.Z = 1.0f - x2 - y2;
            return dir;
        }

        //------------------------------------------------------------
        /// <summary>
        /// XMLに書き出す。
        /// </summary>
        /// <param name="aXML"></param>
        /// <param name="aName"></param>
        public void WriteXml(XmlWriter aXML, string aName)
        {
            aXML.WriteStartElement(aName);
            {
                aXML.WriteAttributeString("x", X.ToString());
                aXML.WriteAttributeString("y", Y.ToString());
                aXML.WriteAttributeString("z", Z.ToString());
                aXML.WriteAttributeString("w", W.ToString());
            }
            aXML.WriteEndElement();
        }
    }
}
