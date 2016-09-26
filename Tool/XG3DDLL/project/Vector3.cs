using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace CrossFramework.XG3D
{
    /// <summary>
    /// 3次元ベクトル。
    /// </summary>
    public struct Vector3
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


        //============================================================

        /// <summary>
        /// XMLから読み込む。
        /// </summary>
        /// <param name="aXml"></param>
        /// <returns></returns>
        public static Vector3 FromXml(XmlNode aXml)
        {
            return new Vector3(
                float.Parse(aXml.Attributes["x"].Value)
                , float.Parse(aXml.Attributes["y"].Value)
                , float.Parse(aXml.Attributes["z"].Value)
                );
        }

        //============================================================
        
        //------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        /// <param name="aV"></param>
        public Vector3(float aV) : this(aV, aV, aV)
        {
        }

        //------------------------------------------------------------
        /// <summary>
        /// コンストラクタ。
        /// </summary>
        /// <param name="aX"></param>
        /// <param name="aY"></param>
        /// <param name="aZ"></param>
        public Vector3(float aX, float aY, float aZ)
        {
            X = aX;
            Y = aY;
            Z = aZ;
        }
        
        //============================================================

        //------------------------------------------------------------
        /// <summary>
        /// 長さを取得する。
        /// </summary>
        public float Length()
        {
            float len = (float)Math.Sqrt(X * X + Y * Y + Z * Z);
            if (Math.Abs(len - 1.0f) <= 0.000001f)
            {// ほぼ1.0fのときのための補正コード。
                return 1.0f;
            }
            return len;
        }

        //------------------------------------------------------------
        /// <summary>
        /// 単位ベクトルを取得する。
        /// </summary>
        /// <returns></returns>
        public Vector3 Unit()
        {
            float len = Length();
            if (len == 0.0f)
            {
                return this;
            }
            float rate = 1.0f / len;
            Vector3 vec = this;
            vec.X *= rate;
            vec.Y *= rate;
            vec.Z *= rate;
            return vec;
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
            }
            aXML.WriteEndElement();
        }
    }
}
