
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Roboterarm
{
	struct GUI2Roboter{
        public byte cmd;
        public byte length;
        public float sensor1MinPos;
        public float sensor2MinPos;
        public float sensor1MaxPos;
        public float sensor2MaxPos;
        public float sensor1Pos;
        public float sensor2Pos;
        public ushort crc16;
        public GUI2Roboter(byte cmd, byte length, float sensor1MinPos, float sensor2MinPos, 
            float sensor1MaxPos, float sensor2MaxPos, float sensor1Pos, float sensor2Pos, ushort crc16)
        {
            this.cmd = cmd;
            this.length = length;
            this.sensor1MinPos = sensor1MinPos;
            this.sensor2MinPos = sensor2MinPos;
            this.sensor1MaxPos = sensor1MaxPos;
            this.sensor2MaxPos = sensor2MaxPos;
            this.sensor1Pos = sensor1Pos;
            this.sensor2Pos = sensor2Pos;
            this.crc16 = crc16;
        }
		
	};
	struct Roboter2GUI{
		public byte cmd;
        public byte length;
        public float sensor1Pos;
        public float sensor2Pos;
        public ushort crc16;
        public Roboter2GUI(byte cmd, byte length, float sensor1Pos, float sensor2Pos, ushort crc16)
        {
            this.cmd = cmd;
            this.length = length;
            this.sensor1Pos = sensor1Pos;
            this.sensor2Pos = sensor2Pos;
            this.crc16 = crc16;
        }
	};
    class definitions_Client
    {
        public enum ColorIndex
        {
            RedColor = 0,
            GreenColor
        }
    }

    public class myKeyPressClass
    {
        static long keyPressCount = 0;
        static long backspacePressed = 0;
        static long returnPressed = 0;
        static long escPressed = 0;
        public TextBox textBox1 = new TextBox();
        public void myKeyCounter(object sender, KeyPressEventArgs ex)
        {
            switch (ex.KeyChar)
            {
                // Counts the backspaces.
                case '\b':
                    backspacePressed = backspacePressed + 1;
                    break;
                // Counts the ENTER keys.
                case '\r':
                    returnPressed = returnPressed + 1;
                    break;
                // Counts the ESC keys.  
                case (char)27:
                    escPressed = escPressed + 1;
                    break;
                // Counts all other keys.
                default:
                    keyPressCount = keyPressCount + 1;
                    break;
            }

            textBox1.Text =
                backspacePressed + " backspaces pressed\r\n" +
                escPressed + " escapes pressed\r\n" +
                returnPressed + " returns pressed\r\n" +
                keyPressCount + " other keys pressed\r\n";
            ex.Handled = true;
        }
    }
}
