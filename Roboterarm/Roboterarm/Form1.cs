using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Roboterarm
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            uart.Encoding = Encoding.UTF8;
            getAvailablePorts();
        }

        void getAvailablePorts()
        {
            //! string to get all available port.
            string[] ports = SerialPort.GetPortNames();
            cmbbox_port.Items.AddRange(ports);

        }
        /*
         ************ This part of code belong to the menustrip ********************
         */
        private void Start_Stop_Click(object sender, EventArgs e)
        {
            //make only the start/stop panel visible
            start_stop_panel.Visible = true;
            sensors_panel.Visible = false;
            settings_panel.Visible = false;
            about_panel.Visible = false;
        }

        private void Sensors_Click(object sender, EventArgs e)
        {
            //make only the sensor panel visible
            start_stop_panel.Visible = false;
            sensors_panel.Visible = true;
            settings_panel.Visible = false;
            about_panel.Visible = false;
        }

        private void Settings_Click(object sender, EventArgs e)
        {
            //make only the setting panel visible
            start_stop_panel.Visible = false;
            sensors_panel.Visible = false;
            settings_panel.Visible = true;
            about_panel.Visible = false;
        }

        private void About_Click(object sender, EventArgs e)
        {
            //make only the about panel visibleolor x =
            start_stop_panel.Visible = false;
            sensors_panel.Visible = false;
            settings_panel.Visible = false;
            about_panel.Visible = true;
        }
        /******************** End of menustrip **************************/
        private void btn_connect_Click(object sender, EventArgs e)
        {
            try
            {
                //! Check if the COM setting is OK
                if ((cmbbox_port.Text == "") || (cmbbox_baudrate.Text == ""))
                {
                    LbelConnectionInfo.Text = "Check the COM Port Setting";
                }
                else
                {
                    uart.PortName = cmbbox_port.Text;
                    uart.BaudRate = Convert.ToInt32(cmbbox_baudrate.Text);
                    uart.Open();

                    btn_connect.Enabled = false;
                    btn_disconnect.Enabled = true;
                    btn_Start.Enabled = true;
                    btn_Stop.Enabled = false;
                    btn_Start.BackColor = Color.Lime;
                    btn_Stop.BackColor = Color.FromArgb(0xF0F0F0);
                    pictureBox1.Image = imageList1.Images[(int)definitions_Client.ColorIndex.GreenColor];
                    label_connection.Text = "Connected";
                    label_connection.ForeColor = Color.Green;
                    LbelConnectionInfo.Text = "";
                    //uart.DataReceived += uart_DataReceived;
                }
            }
            catch
            {
                LbelConnectionInfo.Text = "";

            }

        }

        private void btn_disconnect_Click(object sender, EventArgs e)
        {
            uart.Close();
            btn_connect.Enabled = true;
            btn_disconnect.Enabled = false;
            btn_Start.Enabled = false;
            btn_Stop.Enabled = false;
            btn_Start.BackColor = Color.FromArgb(0xF0F0F0);
            btn_Stop.BackColor = Color.FromArgb(0xF0F0F0);
            pictureBox1.Image = imageList1.Images[(int)definitions_Client.ColorIndex.RedColor];
            label_connection.Text = "Disconnected";
            label_connection.ForeColor = Color.Red;
        }

        private void btn_Stop_Click(object sender, EventArgs e)
        {
            if (btn_disconnect.Enabled && !btn_Start.Enabled)
                btn_Stop.Enabled = true;
            else
                btn_Stop.Enabled = false;

            btn_Stop.Enabled = false;
            btn_Start.Enabled = true;
            btn_Stop.BackColor = Color.FromArgb(0xF0F0F0);
            btn_Start.BackColor = Color.Lime;
        }

        private void btn_Start_Click(object sender, EventArgs e)
        {
            if (btn_disconnect.Enabled && !btn_Stop.Enabled)
                btn_Start.Enabled = true;
            else
                btn_Start.Enabled = false;

            btn_Start.Enabled = false;
            btn_Stop.Enabled = true;
            btn_Start.BackColor = Color.FromArgb(0xF0F0F0);
            btn_Stop.BackColor = Color.Red;
        }

        /* put only number in text box */
        private void txtbox_S1_distance_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != '.'))
            {
                e.Handled = true;
            }

            // only allow one decimal point
            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
            {
                e.Handled = true;
            }
        }
        /* put only number in text box */
        private void txtbox_S2_distance_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) &&(e.KeyChar != '.'))
            {
                e.Handled = true;
            }

            // only allow one decimal point
            if ((e.KeyChar == '.') && ((sender as TextBox).Text.IndexOf('.') > -1))
            {
                e.Handled = true;
            }
        }

    }
}
