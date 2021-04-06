
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Roboterarm
{
	struct GUI2Roboter{
		public :
		unsigned char cmd;
		unsigned char length;
		float sensor1MinPos;
		float sensor2MinPos;
		float sensor1MaxPos;
		float sensor2MaxPos;
		float sensor1Pos;
		float sensor2Pos;
		unsigned short crc16;
		
	};
	struct Roboter2GUI{
		public :
		unsigned char cmd;
		unsigned char length;
		float sensor1Pos;
		float sensor2Pos;
		unsigned short crc16;		
	};
    class definitions_Client
    {
        public enum ColorIndex
        {
            RedColor = 0,
            GreenColor
        }
    }
}
