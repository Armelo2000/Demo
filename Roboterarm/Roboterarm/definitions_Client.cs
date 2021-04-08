
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Roboterarm
{
	struct GUI2Roboter{ // 30 bytes
        public ushort cmd;
        public byte length;
        public byte unit;
        public float sensor1MinPos;
        public float sensor2MinPos;
        public float sensor1MaxPos;
        public float sensor2MaxPos;
        public float sensor1Pos;
        public float sensor2Pos;
        public ushort crc16;
        public GUI2Roboter(ushort cmd = 0, byte length = 0, float sensor1MinPos = 0f, float sensor2MinPos = 0f, 
            float sensor1MaxPos= 0f, float sensor2MaxPos = 0f, float sensor1Pos = 0f, float sensor2Pos = 0f, byte unit = 0, ushort crc16 = 0)
        {
            this.cmd = cmd;
            this.length = length;
            this.sensor1MinPos = sensor1MinPos;
            this.sensor2MinPos = sensor2MinPos;
            this.sensor1MaxPos = sensor1MaxPos;
            this.sensor2MaxPos = sensor2MaxPos;
            this.sensor1Pos = sensor1Pos;
            this.sensor2Pos = sensor2Pos;
            this.unit = unit;
            this.crc16 = crc16;
        }
		
	};
	struct Roboter2GUI{ // 14 bytes
		public ushort cmd;
        public byte length;
        public byte unit;
        public float sensor1Pos;
        public float sensor2Pos;
        public ushort crc16;
        public Roboter2GUI(ushort cmd = 0, byte length = 0, float sensor1Pos = 0f, float sensor2Pos = 0f, byte unit = 0, ushort crc16 = 0)
        {
            this.cmd = cmd;
            this.length = length;
            this.sensor1Pos = sensor1Pos;
            this.sensor2Pos = sensor2Pos;
            this.unit = unit;
            this.crc16 = crc16;
        }
	};

    struct teststruct
    {
        //public byte x1;
        //public byte x2;
        //public byte x3;
        public float x5;
        //public byte x4;
    };
    class definitions_Client
    {
        public enum ColorIndex
        {
            RedColor = 0,
            GreenColor
        }

        public String CollectGUI2Roboter2String(GUI2Roboter tStruct)
        {
            return ($"{tStruct.cmd}:{tStruct.length}:{tStruct.unit}:{tStruct.sensor1MinPos}:{tStruct.sensor2MinPos}:{tStruct.sensor1MaxPos}:{tStruct.sensor2MaxPos}:" +
                $"{tStruct.sensor1Pos}:{tStruct.sensor2Pos}:{tStruct.crc16}");
        }
        public String CollectRoboter2GUI2String(Roboter2GUI tStruct)
        {
            return ($"{tStruct.cmd}:{tStruct.length}:{tStruct.unit}:" +
                $"{tStruct.sensor1Pos}:{tStruct.sensor2Pos}:{tStruct.crc16}:");
        }
    }

}
