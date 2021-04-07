namespace Roboterarm
{
    partial class Form1
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.uart = new System.IO.Ports.SerialPort(this.components);
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.Start_Stop = new System.Windows.Forms.ToolStripMenuItem();
            this.Sensors = new System.Windows.Forms.ToolStripMenuItem();
            this.Settings = new System.Windows.Forms.ToolStripMenuItem();
            this.About = new System.Windows.Forms.ToolStripMenuItem();
            this.start_stop_panel = new System.Windows.Forms.Panel();
            this.grbox_start_stop = new System.Windows.Forms.GroupBox();
            this.btn_Stop = new System.Windows.Forms.Button();
            this.btn_Start = new System.Windows.Forms.Button();
            this.grbox_Roboter = new System.Windows.Forms.GroupBox();
            this.txtbox_S2_distance = new System.Windows.Forms.TextBox();
            this.txtbox_S1_distance = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.chbox_sensor2_DirInvert = new System.Windows.Forms.CheckBox();
            this.btn_S2Right = new System.Windows.Forms.Button();
            this.btn_S2Left = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.chbox_sensor1_DirInvert = new System.Windows.Forms.CheckBox();
            this.btn_S1Right = new System.Windows.Forms.Button();
            this.btn_S1Left = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.cmbbox_S2_unit = new System.Windows.Forms.ComboBox();
            this.cmbbox_S1_unit = new System.Windows.Forms.ComboBox();
            this.txtbox_S2_distanceR_Only = new System.Windows.Forms.TextBox();
            this.label_distance = new System.Windows.Forms.Label();
            this.txtbox_S1_distanceR_Only = new System.Windows.Forms.TextBox();
            this.label_S2_distance = new System.Windows.Forms.Label();
            this.label_S1_distance = new System.Windows.Forms.Label();
            this.grbox_connect = new System.Windows.Forms.GroupBox();
            this.LbelConnectionInfo = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label_connection = new System.Windows.Forms.Label();
            this.btn_disconnect = new System.Windows.Forms.Button();
            this.btn_connect = new System.Windows.Forms.Button();
            this.sensors_panel = new System.Windows.Forms.Panel();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.btn_save_sensors = new System.Windows.Forms.Button();
            this.sensorMax = new System.Windows.Forms.Label();
            this.sensorMin = new System.Windows.Forms.Label();
            this.cmbboxS2Max = new System.Windows.Forms.ComboBox();
            this.cmbboxS1Max = new System.Windows.Forms.ComboBox();
            this.cmbboxS2Min = new System.Windows.Forms.ComboBox();
            this.cmbboxS1Min = new System.Windows.Forms.ComboBox();
            this.txtsensor2Max = new System.Windows.Forms.TextBox();
            this.txtsensor1Max = new System.Windows.Forms.TextBox();
            this.txtsensor2Min = new System.Windows.Forms.TextBox();
            this.txtsensor1Min = new System.Windows.Forms.TextBox();
            this.sensor2 = new System.Windows.Forms.Label();
            this.sensor1 = new System.Windows.Forms.Label();
            this.settings_panel = new System.Windows.Forms.Panel();
            this.button2 = new System.Windows.Forms.Button();
            this.grboxSetting = new System.Windows.Forms.GroupBox();
            this.btn_save_setting = new System.Windows.Forms.Button();
            this.cmbbox_baudrate = new System.Windows.Forms.ComboBox();
            this.label_baudrate = new System.Windows.Forms.Label();
            this.cmbbox_port = new System.Windows.Forms.ComboBox();
            this.label_port = new System.Windows.Forms.Label();
            this.about_panel = new System.Windows.Forms.Panel();
            this.DeveloperInfo = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_close_about_panel = new System.Windows.Forms.Button();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.menuStrip1.SuspendLayout();
            this.start_stop_panel.SuspendLayout();
            this.grbox_start_stop.SuspendLayout();
            this.grbox_Roboter.SuspendLayout();
            this.grbox_connect.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.sensors_panel.SuspendLayout();
            this.settings_panel.SuspendLayout();
            this.grboxSetting.SuspendLayout();
            this.about_panel.SuspendLayout();
            this.DeveloperInfo.SuspendLayout();
            this.SuspendLayout();
            // 
            // uart
            // 
            this.uart.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.uart_DataReceived);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Start_Stop,
            this.Sensors,
            this.Settings,
            this.About});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // Start_Stop
            // 
            this.Start_Stop.Name = "Start_Stop";
            this.Start_Stop.Size = new System.Drawing.Size(72, 20);
            this.Start_Stop.Text = "Start-Stop";
            this.Start_Stop.Click += new System.EventHandler(this.Start_Stop_Click);
            // 
            // Sensors
            // 
            this.Sensors.Name = "Sensors";
            this.Sensors.Size = new System.Drawing.Size(59, 20);
            this.Sensors.Text = "Sensors";
            this.Sensors.Click += new System.EventHandler(this.Sensors_Click);
            // 
            // Settings
            // 
            this.Settings.Name = "Settings";
            this.Settings.Size = new System.Drawing.Size(61, 20);
            this.Settings.Text = "Settings";
            this.Settings.Click += new System.EventHandler(this.Settings_Click);
            // 
            // About
            // 
            this.About.Name = "About";
            this.About.Size = new System.Drawing.Size(52, 20);
            this.About.Text = "About";
            this.About.Click += new System.EventHandler(this.About_Click);
            // 
            // start_stop_panel
            // 
            this.start_stop_panel.Controls.Add(this.grbox_start_stop);
            this.start_stop_panel.Controls.Add(this.grbox_Roboter);
            this.start_stop_panel.Controls.Add(this.grbox_connect);
            this.start_stop_panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.start_stop_panel.Location = new System.Drawing.Point(0, 0);
            this.start_stop_panel.Name = "start_stop_panel";
            this.start_stop_panel.Size = new System.Drawing.Size(800, 450);
            this.start_stop_panel.TabIndex = 2;
            // 
            // grbox_start_stop
            // 
            this.grbox_start_stop.Controls.Add(this.btn_Stop);
            this.grbox_start_stop.Controls.Add(this.btn_Start);
            this.grbox_start_stop.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.grbox_start_stop.Location = new System.Drawing.Point(12, 251);
            this.grbox_start_stop.Name = "grbox_start_stop";
            this.grbox_start_stop.Size = new System.Drawing.Size(268, 135);
            this.grbox_start_stop.TabIndex = 2;
            this.grbox_start_stop.TabStop = false;
            this.grbox_start_stop.Text = "Start/Stop";
            // 
            // btn_Stop
            // 
            this.btn_Stop.BackColor = System.Drawing.SystemColors.ControlLight;
            this.btn_Stop.Enabled = false;
            this.btn_Stop.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_Stop.Location = new System.Drawing.Point(146, 45);
            this.btn_Stop.Name = "btn_Stop";
            this.btn_Stop.Size = new System.Drawing.Size(102, 39);
            this.btn_Stop.TabIndex = 1;
            this.btn_Stop.Text = "STOP";
            this.btn_Stop.UseVisualStyleBackColor = false;
            this.btn_Stop.Click += new System.EventHandler(this.btn_Stop_Click);
            // 
            // btn_Start
            // 
            this.btn_Start.BackColor = System.Drawing.SystemColors.ControlLight;
            this.btn_Start.Enabled = false;
            this.btn_Start.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_Start.Location = new System.Drawing.Point(19, 45);
            this.btn_Start.Name = "btn_Start";
            this.btn_Start.Size = new System.Drawing.Size(102, 39);
            this.btn_Start.TabIndex = 0;
            this.btn_Start.Text = "START";
            this.btn_Start.UseVisualStyleBackColor = false;
            this.btn_Start.Click += new System.EventHandler(this.btn_Start_Click);
            // 
            // grbox_Roboter
            // 
            this.grbox_Roboter.Controls.Add(this.txtbox_S2_distance);
            this.grbox_Roboter.Controls.Add(this.txtbox_S1_distance);
            this.grbox_Roboter.Controls.Add(this.label8);
            this.grbox_Roboter.Controls.Add(this.chbox_sensor2_DirInvert);
            this.grbox_Roboter.Controls.Add(this.btn_S2Right);
            this.grbox_Roboter.Controls.Add(this.btn_S2Left);
            this.grbox_Roboter.Controls.Add(this.label7);
            this.grbox_Roboter.Controls.Add(this.chbox_sensor1_DirInvert);
            this.grbox_Roboter.Controls.Add(this.btn_S1Right);
            this.grbox_Roboter.Controls.Add(this.btn_S1Left);
            this.grbox_Roboter.Controls.Add(this.label4);
            this.grbox_Roboter.Controls.Add(this.cmbbox_S2_unit);
            this.grbox_Roboter.Controls.Add(this.cmbbox_S1_unit);
            this.grbox_Roboter.Controls.Add(this.txtbox_S2_distanceR_Only);
            this.grbox_Roboter.Controls.Add(this.label_distance);
            this.grbox_Roboter.Controls.Add(this.txtbox_S1_distanceR_Only);
            this.grbox_Roboter.Controls.Add(this.label_S2_distance);
            this.grbox_Roboter.Controls.Add(this.label_S1_distance);
            this.grbox_Roboter.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.grbox_Roboter.Location = new System.Drawing.Point(303, 54);
            this.grbox_Roboter.Name = "grbox_Roboter";
            this.grbox_Roboter.Size = new System.Drawing.Size(485, 384);
            this.grbox_Roboter.TabIndex = 2;
            this.grbox_Roboter.TabStop = false;
            this.grbox_Roboter.Text = "Data";
            // 
            // txtbox_S2_distance
            // 
            this.txtbox_S2_distance.Location = new System.Drawing.Point(248, 138);
            this.txtbox_S2_distance.Name = "txtbox_S2_distance";
            this.txtbox_S2_distance.Size = new System.Drawing.Size(121, 23);
            this.txtbox_S2_distance.TabIndex = 21;
            // 
            // txtbox_S1_distance
            // 
            this.txtbox_S1_distance.Location = new System.Drawing.Point(248, 90);
            this.txtbox_S1_distance.Name = "txtbox_S1_distance";
            this.txtbox_S1_distance.Size = new System.Drawing.Size(121, 23);
            this.txtbox_S1_distance.TabIndex = 20;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(22, 259);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(69, 17);
            this.label8.TabIndex = 19;
            this.label8.Text = "Sensor 2 ";
            // 
            // chbox_sensor2_DirInvert
            // 
            this.chbox_sensor2_DirInvert.AutoSize = true;
            this.chbox_sensor2_DirInvert.Location = new System.Drawing.Point(358, 258);
            this.chbox_sensor2_DirInvert.Name = "chbox_sensor2_DirInvert";
            this.chbox_sensor2_DirInvert.Size = new System.Drawing.Size(62, 21);
            this.chbox_sensor2_DirInvert.TabIndex = 18;
            this.chbox_sensor2_DirInvert.Text = "Invert";
            this.chbox_sensor2_DirInvert.UseVisualStyleBackColor = true;
            // 
            // btn_S2Right
            // 
            this.btn_S2Right.Location = new System.Drawing.Point(248, 246);
            this.btn_S2Right.Name = "btn_S2Right";
            this.btn_S2Right.Size = new System.Drawing.Size(88, 33);
            this.btn_S2Right.TabIndex = 17;
            this.btn_S2Right.Text = "Right";
            this.btn_S2Right.UseVisualStyleBackColor = true;
            this.btn_S2Right.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn_S2Right_MouseDown);
            this.btn_S2Right.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn_S2Right_MouseUp);
            // 
            // btn_S2Left
            // 
            this.btn_S2Left.Location = new System.Drawing.Point(111, 246);
            this.btn_S2Left.Name = "btn_S2Left";
            this.btn_S2Left.Size = new System.Drawing.Size(88, 33);
            this.btn_S2Left.TabIndex = 16;
            this.btn_S2Left.Text = "Left";
            this.btn_S2Left.UseVisualStyleBackColor = true;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(22, 210);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(69, 17);
            this.label7.TabIndex = 15;
            this.label7.Text = "Sensor 1 ";
            // 
            // chbox_sensor1_DirInvert
            // 
            this.chbox_sensor1_DirInvert.AutoSize = true;
            this.chbox_sensor1_DirInvert.Location = new System.Drawing.Point(358, 209);
            this.chbox_sensor1_DirInvert.Name = "chbox_sensor1_DirInvert";
            this.chbox_sensor1_DirInvert.Size = new System.Drawing.Size(62, 21);
            this.chbox_sensor1_DirInvert.TabIndex = 14;
            this.chbox_sensor1_DirInvert.Text = "Invert";
            this.chbox_sensor1_DirInvert.UseVisualStyleBackColor = true;
            // 
            // btn_S1Right
            // 
            this.btn_S1Right.Location = new System.Drawing.Point(248, 197);
            this.btn_S1Right.Name = "btn_S1Right";
            this.btn_S1Right.Size = new System.Drawing.Size(88, 33);
            this.btn_S1Right.TabIndex = 13;
            this.btn_S1Right.Text = "Right";
            this.btn_S1Right.UseVisualStyleBackColor = true;
            this.btn_S1Right.KeyDown += new System.Windows.Forms.KeyEventHandler(this.btn_S1Right_KeyDown);
            this.btn_S1Right.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.btn_S1Right_KeyPress);
            // 
            // btn_S1Left
            // 
            this.btn_S1Left.Location = new System.Drawing.Point(111, 197);
            this.btn_S1Left.Name = "btn_S1Left";
            this.btn_S1Left.Size = new System.Drawing.Size(88, 33);
            this.btn_S1Left.TabIndex = 12;
            this.btn_S1Left.Text = "Left";
            this.btn_S1Left.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(387, 58);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(52, 17);
            this.label4.TabIndex = 11;
            this.label4.Text = "mm/cm";
            // 
            // cmbbox_S2_unit
            // 
            this.cmbbox_S2_unit.FormattingEnabled = true;
            this.cmbbox_S2_unit.Items.AddRange(new object[] {
            "mm",
            "cm"});
            this.cmbbox_S2_unit.Location = new System.Drawing.Point(384, 138);
            this.cmbbox_S2_unit.Name = "cmbbox_S2_unit";
            this.cmbbox_S2_unit.Size = new System.Drawing.Size(54, 24);
            this.cmbbox_S2_unit.TabIndex = 10;
            // 
            // cmbbox_S1_unit
            // 
            this.cmbbox_S1_unit.FormattingEnabled = true;
            this.cmbbox_S1_unit.Items.AddRange(new object[] {
            "mm",
            "cm"});
            this.cmbbox_S1_unit.Location = new System.Drawing.Point(385, 90);
            this.cmbbox_S1_unit.Name = "cmbbox_S1_unit";
            this.cmbbox_S1_unit.Size = new System.Drawing.Size(54, 24);
            this.cmbbox_S1_unit.TabIndex = 9;
            // 
            // txtbox_S2_distanceR_Only
            // 
            this.txtbox_S2_distanceR_Only.Location = new System.Drawing.Point(111, 138);
            this.txtbox_S2_distanceR_Only.Name = "txtbox_S2_distanceR_Only";
            this.txtbox_S2_distanceR_Only.ReadOnly = true;
            this.txtbox_S2_distanceR_Only.Size = new System.Drawing.Size(121, 23);
            this.txtbox_S2_distanceR_Only.TabIndex = 8;
            this.txtbox_S2_distanceR_Only.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtbox_S2_distance_KeyPress);
            // 
            // label_distance
            // 
            this.label_distance.AutoSize = true;
            this.label_distance.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_distance.Location = new System.Drawing.Point(213, 58);
            this.label_distance.Name = "label_distance";
            this.label_distance.Size = new System.Drawing.Size(63, 17);
            this.label_distance.TabIndex = 7;
            this.label_distance.Text = "Distance";
            // 
            // txtbox_S1_distanceR_Only
            // 
            this.txtbox_S1_distanceR_Only.Location = new System.Drawing.Point(111, 90);
            this.txtbox_S1_distanceR_Only.Name = "txtbox_S1_distanceR_Only";
            this.txtbox_S1_distanceR_Only.ReadOnly = true;
            this.txtbox_S1_distanceR_Only.Size = new System.Drawing.Size(121, 23);
            this.txtbox_S1_distanceR_Only.TabIndex = 6;
            this.txtbox_S1_distanceR_Only.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtbox_S1_distance_KeyPress);
            // 
            // label_S2_distance
            // 
            this.label_S2_distance.AutoSize = true;
            this.label_S2_distance.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_S2_distance.Location = new System.Drawing.Point(25, 141);
            this.label_S2_distance.Name = "label_S2_distance";
            this.label_S2_distance.Size = new System.Drawing.Size(69, 17);
            this.label_S2_distance.TabIndex = 5;
            this.label_S2_distance.Text = "Sensor 2 ";
            // 
            // label_S1_distance
            // 
            this.label_S1_distance.AutoSize = true;
            this.label_S1_distance.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_S1_distance.Location = new System.Drawing.Point(25, 93);
            this.label_S1_distance.Name = "label_S1_distance";
            this.label_S1_distance.Size = new System.Drawing.Size(69, 17);
            this.label_S1_distance.TabIndex = 4;
            this.label_S1_distance.Text = "Sensor 1 ";
            // 
            // grbox_connect
            // 
            this.grbox_connect.Controls.Add(this.LbelConnectionInfo);
            this.grbox_connect.Controls.Add(this.pictureBox1);
            this.grbox_connect.Controls.Add(this.label_connection);
            this.grbox_connect.Controls.Add(this.btn_disconnect);
            this.grbox_connect.Controls.Add(this.btn_connect);
            this.grbox_connect.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.grbox_connect.Location = new System.Drawing.Point(12, 45);
            this.grbox_connect.Name = "grbox_connect";
            this.grbox_connect.Size = new System.Drawing.Size(268, 184);
            this.grbox_connect.TabIndex = 1;
            this.grbox_connect.TabStop = false;
            this.grbox_connect.Text = "Connection";
            // 
            // LbelConnectionInfo
            // 
            this.LbelConnectionInfo.AutoSize = true;
            this.LbelConnectionInfo.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LbelConnectionInfo.ForeColor = System.Drawing.Color.Red;
            this.LbelConnectionInfo.Location = new System.Drawing.Point(37, 153);
            this.LbelConnectionInfo.Name = "LbelConnectionInfo";
            this.LbelConnectionInfo.Size = new System.Drawing.Size(0, 15);
            this.LbelConnectionInfo.TabIndex = 4;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::Roboterarm.Properties.Resources.redSphere_Small;
            this.pictureBox1.Location = new System.Drawing.Point(78, 103);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(21, 20);
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            // 
            // label_connection
            // 
            this.label_connection.AutoSize = true;
            this.label_connection.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label_connection.ForeColor = System.Drawing.Color.Red;
            this.label_connection.Location = new System.Drawing.Point(102, 105);
            this.label_connection.Name = "label_connection";
            this.label_connection.Size = new System.Drawing.Size(94, 17);
            this.label_connection.TabIndex = 2;
            this.label_connection.Text = "Disconnected";
            // 
            // btn_disconnect
            // 
            this.btn_disconnect.Enabled = false;
            this.btn_disconnect.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_disconnect.Location = new System.Drawing.Point(136, 45);
            this.btn_disconnect.Name = "btn_disconnect";
            this.btn_disconnect.Size = new System.Drawing.Size(112, 39);
            this.btn_disconnect.TabIndex = 1;
            this.btn_disconnect.Text = "Disconnect";
            this.btn_disconnect.UseVisualStyleBackColor = true;
            this.btn_disconnect.Click += new System.EventHandler(this.btn_disconnect_Click);
            // 
            // btn_connect
            // 
            this.btn_connect.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_connect.Location = new System.Drawing.Point(13, 45);
            this.btn_connect.Name = "btn_connect";
            this.btn_connect.Size = new System.Drawing.Size(108, 39);
            this.btn_connect.TabIndex = 0;
            this.btn_connect.Text = "Connect";
            this.btn_connect.UseVisualStyleBackColor = true;
            this.btn_connect.Click += new System.EventHandler(this.btn_connect_Click);
            // 
            // sensors_panel
            // 
            this.sensors_panel.Controls.Add(this.label6);
            this.sensors_panel.Controls.Add(this.label5);
            this.sensors_panel.Controls.Add(this.btn_save_sensors);
            this.sensors_panel.Controls.Add(this.sensorMax);
            this.sensors_panel.Controls.Add(this.sensorMin);
            this.sensors_panel.Controls.Add(this.cmbboxS2Max);
            this.sensors_panel.Controls.Add(this.cmbboxS1Max);
            this.sensors_panel.Controls.Add(this.cmbboxS2Min);
            this.sensors_panel.Controls.Add(this.cmbboxS1Min);
            this.sensors_panel.Controls.Add(this.txtsensor2Max);
            this.sensors_panel.Controls.Add(this.txtsensor1Max);
            this.sensors_panel.Controls.Add(this.txtsensor2Min);
            this.sensors_panel.Controls.Add(this.txtsensor1Min);
            this.sensors_panel.Controls.Add(this.sensor2);
            this.sensors_panel.Controls.Add(this.sensor1);
            this.sensors_panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.sensors_panel.Location = new System.Drawing.Point(0, 0);
            this.sensors_panel.Name = "sensors_panel";
            this.sensors_panel.Size = new System.Drawing.Size(800, 450);
            this.sensors_panel.TabIndex = 3;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(325, 121);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(52, 17);
            this.label6.TabIndex = 14;
            this.label6.Text = "mm/cm";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(585, 121);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(52, 17);
            this.label5.TabIndex = 13;
            this.label5.Text = "mm/cm";
            // 
            // btn_save_sensors
            // 
            this.btn_save_sensors.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_save_sensors.Location = new System.Drawing.Point(352, 258);
            this.btn_save_sensors.Name = "btn_save_sensors";
            this.btn_save_sensors.Size = new System.Drawing.Size(136, 49);
            this.btn_save_sensors.TabIndex = 12;
            this.btn_save_sensors.Text = "Save";
            this.btn_save_sensors.UseVisualStyleBackColor = true;
            // 
            // sensorMax
            // 
            this.sensorMax.AutoSize = true;
            this.sensorMax.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.sensorMax.Location = new System.Drawing.Point(481, 121);
            this.sensorMax.Name = "sensorMax";
            this.sensorMax.Size = new System.Drawing.Size(84, 17);
            this.sensorMax.TabIndex = 11;
            this.sensorMax.Text = "Max. Values";
            // 
            // sensorMin
            // 
            this.sensorMin.AutoSize = true;
            this.sensorMin.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.sensorMin.Location = new System.Drawing.Point(216, 121);
            this.sensorMin.Name = "sensorMin";
            this.sensorMin.Size = new System.Drawing.Size(81, 17);
            this.sensorMin.TabIndex = 10;
            this.sensorMin.Text = "Min. Values";
            // 
            // cmbboxS2Max
            // 
            this.cmbboxS2Max.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmbboxS2Max.FormattingEnabled = true;
            this.cmbboxS2Max.Items.AddRange(new object[] {
            "mm",
            "cm"});
            this.cmbboxS2Max.Location = new System.Drawing.Point(588, 194);
            this.cmbboxS2Max.Name = "cmbboxS2Max";
            this.cmbboxS2Max.Size = new System.Drawing.Size(47, 24);
            this.cmbboxS2Max.TabIndex = 9;
            // 
            // cmbboxS1Max
            // 
            this.cmbboxS1Max.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmbboxS1Max.FormattingEnabled = true;
            this.cmbboxS1Max.Items.AddRange(new object[] {
            "mm",
            "cm"});
            this.cmbboxS1Max.Location = new System.Drawing.Point(588, 156);
            this.cmbboxS1Max.Name = "cmbboxS1Max";
            this.cmbboxS1Max.Size = new System.Drawing.Size(47, 24);
            this.cmbboxS1Max.TabIndex = 8;
            // 
            // cmbboxS2Min
            // 
            this.cmbboxS2Min.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmbboxS2Min.FormattingEnabled = true;
            this.cmbboxS2Min.Items.AddRange(new object[] {
            "mm",
            "cm"});
            this.cmbboxS2Min.Location = new System.Drawing.Point(328, 195);
            this.cmbboxS2Min.Name = "cmbboxS2Min";
            this.cmbboxS2Min.Size = new System.Drawing.Size(47, 24);
            this.cmbboxS2Min.TabIndex = 7;
            // 
            // cmbboxS1Min
            // 
            this.cmbboxS1Min.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cmbboxS1Min.FormattingEnabled = true;
            this.cmbboxS1Min.Items.AddRange(new object[] {
            "mm",
            "cm"});
            this.cmbboxS1Min.Location = new System.Drawing.Point(328, 156);
            this.cmbboxS1Min.Name = "cmbboxS1Min";
            this.cmbboxS1Min.Size = new System.Drawing.Size(47, 24);
            this.cmbboxS1Min.TabIndex = 6;
            // 
            // txtsensor2Max
            // 
            this.txtsensor2Max.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtsensor2Max.Location = new System.Drawing.Point(458, 195);
            this.txtsensor2Max.Name = "txtsensor2Max";
            this.txtsensor2Max.Size = new System.Drawing.Size(124, 23);
            this.txtsensor2Max.TabIndex = 5;
            // 
            // txtsensor1Max
            // 
            this.txtsensor1Max.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtsensor1Max.Location = new System.Drawing.Point(458, 156);
            this.txtsensor1Max.Name = "txtsensor1Max";
            this.txtsensor1Max.Size = new System.Drawing.Size(124, 23);
            this.txtsensor1Max.TabIndex = 4;
            // 
            // txtsensor2Min
            // 
            this.txtsensor2Min.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtsensor2Min.Location = new System.Drawing.Point(198, 195);
            this.txtsensor2Min.Name = "txtsensor2Min";
            this.txtsensor2Min.Size = new System.Drawing.Size(124, 23);
            this.txtsensor2Min.TabIndex = 3;
            // 
            // txtsensor1Min
            // 
            this.txtsensor1Min.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtsensor1Min.Location = new System.Drawing.Point(198, 157);
            this.txtsensor1Min.Name = "txtsensor1Min";
            this.txtsensor1Min.Size = new System.Drawing.Size(124, 23);
            this.txtsensor1Min.TabIndex = 2;
            // 
            // sensor2
            // 
            this.sensor2.AutoSize = true;
            this.sensor2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.sensor2.Location = new System.Drawing.Point(114, 195);
            this.sensor2.Name = "sensor2";
            this.sensor2.Size = new System.Drawing.Size(65, 17);
            this.sensor2.TabIndex = 1;
            this.sensor2.Text = "Sensor 2";
            // 
            // sensor1
            // 
            this.sensor1.AutoSize = true;
            this.sensor1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.sensor1.Location = new System.Drawing.Point(114, 157);
            this.sensor1.Name = "sensor1";
            this.sensor1.Size = new System.Drawing.Size(65, 17);
            this.sensor1.TabIndex = 0;
            this.sensor1.Text = "Sensor 1";
            // 
            // settings_panel
            // 
            this.settings_panel.Controls.Add(this.button2);
            this.settings_panel.Controls.Add(this.grboxSetting);
            this.settings_panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.settings_panel.Location = new System.Drawing.Point(0, 0);
            this.settings_panel.Name = "settings_panel";
            this.settings_panel.Size = new System.Drawing.Size(800, 450);
            this.settings_panel.TabIndex = 4;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(0, 0);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 3;
            this.button2.Text = "button2";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // grboxSetting
            // 
            this.grboxSetting.Controls.Add(this.btn_save_setting);
            this.grboxSetting.Controls.Add(this.cmbbox_baudrate);
            this.grboxSetting.Controls.Add(this.label_baudrate);
            this.grboxSetting.Controls.Add(this.cmbbox_port);
            this.grboxSetting.Controls.Add(this.label_port);
            this.grboxSetting.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.grboxSetting.Location = new System.Drawing.Point(129, 90);
            this.grboxSetting.Name = "grboxSetting";
            this.grboxSetting.Size = new System.Drawing.Size(568, 272);
            this.grboxSetting.TabIndex = 2;
            this.grboxSetting.TabStop = false;
            this.grboxSetting.Text = "Port Setting";
            // 
            // btn_save_setting
            // 
            this.btn_save_setting.Location = new System.Drawing.Point(263, 205);
            this.btn_save_setting.Name = "btn_save_setting";
            this.btn_save_setting.Size = new System.Drawing.Size(110, 45);
            this.btn_save_setting.TabIndex = 4;
            this.btn_save_setting.Text = "Save";
            this.btn_save_setting.UseVisualStyleBackColor = true;
            // 
            // cmbbox_baudrate
            // 
            this.cmbbox_baudrate.FormattingEnabled = true;
            this.cmbbox_baudrate.Items.AddRange(new object[] {
            "1200",
            "2400",
            "3200",
            "9600",
            "19200",
            "38400",
            "57600",
            "115200"});
            this.cmbbox_baudrate.Location = new System.Drawing.Point(174, 135);
            this.cmbbox_baudrate.Name = "cmbbox_baudrate";
            this.cmbbox_baudrate.Size = new System.Drawing.Size(262, 28);
            this.cmbbox_baudrate.TabIndex = 2;
            // 
            // label_baudrate
            // 
            this.label_baudrate.AutoSize = true;
            this.label_baudrate.Location = new System.Drawing.Point(43, 143);
            this.label_baudrate.Name = "label_baudrate";
            this.label_baudrate.Size = new System.Drawing.Size(98, 20);
            this.label_baudrate.TabIndex = 3;
            this.label_baudrate.Text = "BAUDRATE";
            // 
            // cmbbox_port
            // 
            this.cmbbox_port.FormattingEnabled = true;
            this.cmbbox_port.Location = new System.Drawing.Point(174, 77);
            this.cmbbox_port.Name = "cmbbox_port";
            this.cmbbox_port.Size = new System.Drawing.Size(262, 28);
            this.cmbbox_port.TabIndex = 0;
            // 
            // label_port
            // 
            this.label_port.AutoSize = true;
            this.label_port.Location = new System.Drawing.Point(43, 77);
            this.label_port.Name = "label_port";
            this.label_port.Size = new System.Drawing.Size(52, 20);
            this.label_port.TabIndex = 1;
            this.label_port.Text = "PORT";
            // 
            // about_panel
            // 
            this.about_panel.Controls.Add(this.DeveloperInfo);
            this.about_panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.about_panel.Location = new System.Drawing.Point(0, 0);
            this.about_panel.Name = "about_panel";
            this.about_panel.Size = new System.Drawing.Size(800, 450);
            this.about_panel.TabIndex = 5;
            // 
            // DeveloperInfo
            // 
            this.DeveloperInfo.Controls.Add(this.label3);
            this.DeveloperInfo.Controls.Add(this.label2);
            this.DeveloperInfo.Controls.Add(this.label1);
            this.DeveloperInfo.Controls.Add(this.btn_close_about_panel);
            this.DeveloperInfo.Font = new System.Drawing.Font("Microsoft Sans Serif", 3F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Millimeter, ((byte)(0)));
            this.DeveloperInfo.Location = new System.Drawing.Point(25, 54);
            this.DeveloperInfo.Name = "DeveloperInfo";
            this.DeveloperInfo.Size = new System.Drawing.Size(743, 348);
            this.DeveloperInfo.TabIndex = 1;
            this.DeveloperInfo.TabStop = false;
            this.DeveloperInfo.Text = "Developer Info";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 4F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Millimeter, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(181, 197);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(319, 20);
            this.label3.TabIndex = 3;
            this.label3.Text = "Distributed in 2021 by Armel Tsannang";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 4F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Millimeter, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(271, 155);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(110, 20);
            this.label2.TabIndex = 2;
            this.label2.Text = "Version : 1.0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 4F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Millimeter, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(271, 118);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(111, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "Roboter Arm";
            // 
            // btn_close_about_panel
            // 
            this.btn_close_about_panel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_close_about_panel.Location = new System.Drawing.Point(636, 293);
            this.btn_close_about_panel.Name = "btn_close_about_panel";
            this.btn_close_about_panel.Size = new System.Drawing.Size(101, 49);
            this.btn_close_about_panel.TabIndex = 0;
            this.btn_close_about_panel.Text = "Close";
            this.btn_close_about_panel.UseVisualStyleBackColor = true;
            // 
            // imageList1
            // 
            this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            this.imageList1.Images.SetKeyName(0, "redSphere_Small.jpg");
            this.imageList1.Images.SetKeyName(1, "greenSphere_Small.jpg");
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.start_stop_panel);
            this.Controls.Add(this.about_panel);
            this.Controls.Add(this.settings_panel);
            this.Controls.Add(this.sensors_panel);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "RoboterArm_V1.0";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.start_stop_panel.ResumeLayout(false);
            this.grbox_start_stop.ResumeLayout(false);
            this.grbox_Roboter.ResumeLayout(false);
            this.grbox_Roboter.PerformLayout();
            this.grbox_connect.ResumeLayout(false);
            this.grbox_connect.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.sensors_panel.ResumeLayout(false);
            this.sensors_panel.PerformLayout();
            this.settings_panel.ResumeLayout(false);
            this.grboxSetting.ResumeLayout(false);
            this.grboxSetting.PerformLayout();
            this.about_panel.ResumeLayout(false);
            this.DeveloperInfo.ResumeLayout(false);
            this.DeveloperInfo.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.IO.Ports.SerialPort uart;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem Start_Stop;
        private System.Windows.Forms.ToolStripMenuItem Sensors;
        private System.Windows.Forms.ToolStripMenuItem Settings;
        private System.Windows.Forms.ToolStripMenuItem About;
        private System.Windows.Forms.Panel start_stop_panel;
        private System.Windows.Forms.Button btn_connect;
        private System.Windows.Forms.Panel sensors_panel;
        private System.Windows.Forms.Panel settings_panel;
        private System.Windows.Forms.Panel about_panel;
        private System.Windows.Forms.Button btn_close_about_panel;
        private System.Windows.Forms.GroupBox DeveloperInfo;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox grbox_connect;
        private System.Windows.Forms.Button btn_save_sensors;
        private System.Windows.Forms.Label sensorMax;
        private System.Windows.Forms.Label sensorMin;
        private System.Windows.Forms.ComboBox cmbboxS2Max;
        private System.Windows.Forms.ComboBox cmbboxS1Max;
        private System.Windows.Forms.ComboBox cmbboxS2Min;
        private System.Windows.Forms.ComboBox cmbboxS1Min;
        private System.Windows.Forms.TextBox txtsensor2Max;
        private System.Windows.Forms.TextBox txtsensor1Max;
        private System.Windows.Forms.TextBox txtsensor2Min;
        private System.Windows.Forms.TextBox txtsensor1Min;
        private System.Windows.Forms.Label sensor2;
        private System.Windows.Forms.Label sensor1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.GroupBox grboxSetting;
        private System.Windows.Forms.Button btn_save_setting;
        private System.Windows.Forms.ComboBox cmbbox_baudrate;
        private System.Windows.Forms.Label label_baudrate;
        private System.Windows.Forms.ComboBox cmbbox_port;
        private System.Windows.Forms.Label label_port;
        private System.Windows.Forms.GroupBox grbox_start_stop;
        private System.Windows.Forms.Button btn_Stop;
        private System.Windows.Forms.Button btn_Start;
        private System.Windows.Forms.GroupBox grbox_Roboter;
        private System.Windows.Forms.Button btn_disconnect;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label_connection;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cmbbox_S2_unit;
        private System.Windows.Forms.ComboBox cmbbox_S1_unit;
        private System.Windows.Forms.TextBox txtbox_S2_distanceR_Only;
        private System.Windows.Forms.Label label_distance;
        private System.Windows.Forms.TextBox txtbox_S1_distanceR_Only;
        private System.Windows.Forms.Label label_S2_distance;
        private System.Windows.Forms.Label label_S1_distance;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.Label LbelConnectionInfo;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.CheckBox chbox_sensor2_DirInvert;
        private System.Windows.Forms.Button btn_S2Right;
        private System.Windows.Forms.Button btn_S2Left;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.CheckBox chbox_sensor1_DirInvert;
        private System.Windows.Forms.Button btn_S1Right;
        private System.Windows.Forms.Button btn_S1Left;
        private System.Windows.Forms.TextBox txtbox_S2_distance;
        private System.Windows.Forms.TextBox txtbox_S1_distance;
    }
}

