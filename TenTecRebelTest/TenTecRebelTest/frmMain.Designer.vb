<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmMain
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Me.SerialPort1 = New System.IO.Ports.SerialPort(Me.components)
        Me.TextBox1 = New System.Windows.Forms.TextBox()
        Me.CheckBox1 = New System.Windows.Forms.CheckBox()
        Me.lblFrequency = New System.Windows.Forms.Label()
        Me.lblRxFrequency = New System.Windows.Forms.Label()
        Me.TableLayoutPanel1 = New System.Windows.Forms.TableLayoutPanel()
        Me.cmdReset = New System.Windows.Forms.Button()
        Me.chkPortOpen = New System.Windows.Forms.CheckBox()
        Me.cmdTuneDown = New System.Windows.Forms.Button()
        Me.cmdTuneUp = New System.Windows.Forms.Button()
        Me.cmdSetFrequency = New System.Windows.Forms.Button()
        Me.cboBandwidth = New System.Windows.Forms.ComboBox()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.cboTuneStep = New System.Windows.Forms.ComboBox()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.cboKeyer = New System.Windows.Forms.ComboBox()
        Me.Label15 = New System.Windows.Forms.Label()
        Me.cboBandEnd = New System.Windows.Forms.ComboBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.lblSMeter = New System.Windows.Forms.Label()
        Me.lblOutputPower = New System.Windows.Forms.Label()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.lblVoltage = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label17 = New System.Windows.Forms.Label()
        Me.cboComPort = New System.Windows.Forms.ComboBox()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.lblKeyerWPM = New System.Windows.Forms.LinkLabel()
        Me.TextBox2 = New System.Windows.Forms.TextBox()
        Me.TableLayoutPanel2 = New System.Windows.Forms.TableLayoutPanel()
        Me.chkDecoder = New System.Windows.Forms.CheckBox()
        Me.hscDecodeThreshhold = New System.Windows.Forms.HScrollBar()
        Me.Label16 = New System.Windows.Forms.Label()
        Me.lblCWStrength = New System.Windows.Forms.Label()
        Me.Label10 = New System.Windows.Forms.Label()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.TableLayoutPanel3 = New System.Windows.Forms.TableLayoutPanel()
        Me.cboBandscan = New System.Windows.Forms.ComboBox()
        Me.Label11 = New System.Windows.Forms.Label()
        Me.Label12 = New System.Windows.Forms.Label()
        Me.Label13 = New System.Windows.Forms.Label()
        Me.Label14 = New System.Windows.Forms.Label()
        Me.lblBandscanBottom = New System.Windows.Forms.LinkLabel()
        Me.lblBandscanTop = New System.Windows.Forms.LinkLabel()
        Me.lblBandscanWidth = New System.Windows.Forms.LinkLabel()
        Me.lblBandscanInterval = New System.Windows.Forms.LinkLabel()
        Me.picBandscan = New System.Windows.Forms.PictureBox()
        Me.TableLayoutPanel1.SuspendLayout()
        Me.TableLayoutPanel2.SuspendLayout()
        Me.GroupBox1.SuspendLayout()
        Me.TableLayoutPanel3.SuspendLayout()
        CType(Me.picBandscan, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'SerialPort1
        '
        Me.SerialPort1.BaudRate = 115200
        Me.SerialPort1.PortName = "COM9"
        '
        'TextBox1
        '
        Me.TextBox1.Location = New System.Drawing.Point(12, 12)
        Me.TextBox1.Multiline = True
        Me.TextBox1.Name = "TextBox1"
        Me.TextBox1.ScrollBars = System.Windows.Forms.ScrollBars.Both
        Me.TextBox1.Size = New System.Drawing.Size(534, 115)
        Me.TextBox1.TabIndex = 0
        '
        'CheckBox1
        '
        Me.CheckBox1.AutoSize = True
        Me.CheckBox1.Enabled = False
        Me.CheckBox1.Location = New System.Drawing.Point(12, 133)
        Me.CheckBox1.Name = "CheckBox1"
        Me.CheckBox1.Size = New System.Drawing.Size(83, 17)
        Me.CheckBox1.TabIndex = 1
        Me.CheckBox1.Text = "Transmitting"
        Me.CheckBox1.UseVisualStyleBackColor = True
        '
        'lblFrequency
        '
        Me.lblFrequency.AutoSize = True
        Me.lblFrequency.Location = New System.Drawing.Point(145, 48)
        Me.lblFrequency.Name = "lblFrequency"
        Me.lblFrequency.Size = New System.Drawing.Size(39, 13)
        Me.lblFrequency.TabIndex = 3
        Me.lblFrequency.Text = "Label1"
        '
        'lblRxFrequency
        '
        Me.lblRxFrequency.AutoSize = True
        Me.lblRxFrequency.Location = New System.Drawing.Point(145, 72)
        Me.lblRxFrequency.Name = "lblRxFrequency"
        Me.lblRxFrequency.Size = New System.Drawing.Size(39, 13)
        Me.lblRxFrequency.TabIndex = 4
        Me.lblRxFrequency.Text = "Label1"
        '
        'TableLayoutPanel1
        '
        Me.TableLayoutPanel1.ColumnCount = 2
        Me.TableLayoutPanel1.ColumnStyles.Add(New System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50.0!))
        Me.TableLayoutPanel1.ColumnStyles.Add(New System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50.0!))
        Me.TableLayoutPanel1.Controls.Add(Me.cmdReset, 1, 1)
        Me.TableLayoutPanel1.Controls.Add(Me.chkPortOpen, 0, 1)
        Me.TableLayoutPanel1.Controls.Add(Me.cmdTuneDown, 0, 7)
        Me.TableLayoutPanel1.Controls.Add(Me.cmdTuneUp, 1, 7)
        Me.TableLayoutPanel1.Controls.Add(Me.cmdSetFrequency, 1, 8)
        Me.TableLayoutPanel1.Controls.Add(Me.cboBandwidth, 1, 9)
        Me.TableLayoutPanel1.Controls.Add(Me.Label7, 0, 9)
        Me.TableLayoutPanel1.Controls.Add(Me.Label8, 0, 10)
        Me.TableLayoutPanel1.Controls.Add(Me.cboTuneStep, 1, 10)
        Me.TableLayoutPanel1.Controls.Add(Me.Label9, 0, 12)
        Me.TableLayoutPanel1.Controls.Add(Me.cboKeyer, 1, 12)
        Me.TableLayoutPanel1.Controls.Add(Me.Label15, 0, 11)
        Me.TableLayoutPanel1.Controls.Add(Me.cboBandEnd, 1, 11)
        Me.TableLayoutPanel1.Controls.Add(Me.Label5, 0, 6)
        Me.TableLayoutPanel1.Controls.Add(Me.lblSMeter, 1, 6)
        Me.TableLayoutPanel1.Controls.Add(Me.lblOutputPower, 1, 5)
        Me.TableLayoutPanel1.Controls.Add(Me.Label4, 0, 5)
        Me.TableLayoutPanel1.Controls.Add(Me.Label3, 0, 4)
        Me.TableLayoutPanel1.Controls.Add(Me.lblVoltage, 1, 4)
        Me.TableLayoutPanel1.Controls.Add(Me.lblRxFrequency, 1, 3)
        Me.TableLayoutPanel1.Controls.Add(Me.lblFrequency, 1, 2)
        Me.TableLayoutPanel1.Controls.Add(Me.Label2, 0, 3)
        Me.TableLayoutPanel1.Controls.Add(Me.Label1, 0, 2)
        Me.TableLayoutPanel1.Controls.Add(Me.Label17, 0, 0)
        Me.TableLayoutPanel1.Controls.Add(Me.cboComPort, 1, 0)
        Me.TableLayoutPanel1.Location = New System.Drawing.Point(12, 156)
        Me.TableLayoutPanel1.Name = "TableLayoutPanel1"
        Me.TableLayoutPanel1.RowCount = 14
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel1.Size = New System.Drawing.Size(285, 348)
        Me.TableLayoutPanel1.TabIndex = 7
        '
        'cmdReset
        '
        Me.cmdReset.Dock = System.Windows.Forms.DockStyle.Fill
        Me.cmdReset.Location = New System.Drawing.Point(145, 27)
        Me.cmdReset.Name = "cmdReset"
        Me.cmdReset.Size = New System.Drawing.Size(137, 18)
        Me.cmdReset.TabIndex = 1
        Me.cmdReset.Text = "Reset Radio"
        Me.cmdReset.UseVisualStyleBackColor = True
        '
        'chkPortOpen
        '
        Me.chkPortOpen.AutoSize = True
        Me.chkPortOpen.Location = New System.Drawing.Point(3, 27)
        Me.chkPortOpen.Name = "chkPortOpen"
        Me.chkPortOpen.Size = New System.Drawing.Size(74, 17)
        Me.chkPortOpen.TabIndex = 0
        Me.chkPortOpen.Text = "Port Open"
        Me.chkPortOpen.UseVisualStyleBackColor = True
        '
        'cmdTuneDown
        '
        Me.cmdTuneDown.Dock = System.Windows.Forms.DockStyle.Fill
        Me.cmdTuneDown.Location = New System.Drawing.Point(3, 171)
        Me.cmdTuneDown.Name = "cmdTuneDown"
        Me.cmdTuneDown.Size = New System.Drawing.Size(136, 18)
        Me.cmdTuneDown.TabIndex = 15
        Me.cmdTuneDown.Text = "Tune Down"
        Me.cmdTuneDown.UseVisualStyleBackColor = True
        '
        'cmdTuneUp
        '
        Me.cmdTuneUp.Dock = System.Windows.Forms.DockStyle.Fill
        Me.cmdTuneUp.Location = New System.Drawing.Point(145, 171)
        Me.cmdTuneUp.Name = "cmdTuneUp"
        Me.cmdTuneUp.Size = New System.Drawing.Size(137, 18)
        Me.cmdTuneUp.TabIndex = 16
        Me.cmdTuneUp.Text = "Tune Up"
        Me.cmdTuneUp.UseVisualStyleBackColor = True
        '
        'cmdSetFrequency
        '
        Me.cmdSetFrequency.Dock = System.Windows.Forms.DockStyle.Fill
        Me.cmdSetFrequency.Location = New System.Drawing.Point(145, 195)
        Me.cmdSetFrequency.Name = "cmdSetFrequency"
        Me.cmdSetFrequency.Size = New System.Drawing.Size(137, 18)
        Me.cmdSetFrequency.TabIndex = 19
        Me.cmdSetFrequency.Text = "Set Frequency"
        Me.cmdSetFrequency.UseVisualStyleBackColor = True
        '
        'cboBandwidth
        '
        Me.cboBandwidth.Dock = System.Windows.Forms.DockStyle.Fill
        Me.cboBandwidth.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboBandwidth.FormattingEnabled = True
        Me.cboBandwidth.Items.AddRange(New Object() {"Wide", "Medium", "Narrow"})
        Me.cboBandwidth.Location = New System.Drawing.Point(145, 219)
        Me.cboBandwidth.Name = "cboBandwidth"
        Me.cboBandwidth.Size = New System.Drawing.Size(137, 21)
        Me.cboBandwidth.TabIndex = 20
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(3, 216)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(57, 13)
        Me.Label7.TabIndex = 21
        Me.Label7.Text = "Bandwidth"
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(3, 240)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(57, 13)
        Me.Label8.TabIndex = 22
        Me.Label8.Text = "Tune Step"
        '
        'cboTuneStep
        '
        Me.cboTuneStep.Dock = System.Windows.Forms.DockStyle.Fill
        Me.cboTuneStep.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboTuneStep.FormattingEnabled = True
        Me.cboTuneStep.Items.AddRange(New Object() {"100 Hz", "1 KHz", "10 KHz"})
        Me.cboTuneStep.Location = New System.Drawing.Point(145, 243)
        Me.cboTuneStep.Name = "cboTuneStep"
        Me.cboTuneStep.Size = New System.Drawing.Size(137, 21)
        Me.cboTuneStep.TabIndex = 23
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(3, 288)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(34, 13)
        Me.Label9.TabIndex = 24
        Me.Label9.Text = "Keyer"
        '
        'cboKeyer
        '
        Me.cboKeyer.Dock = System.Windows.Forms.DockStyle.Fill
        Me.cboKeyer.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboKeyer.FormattingEnabled = True
        Me.cboKeyer.Items.AddRange(New Object() {"Disabled", "Straight Key", "Iambic", "Tune"})
        Me.cboKeyer.Location = New System.Drawing.Point(145, 291)
        Me.cboKeyer.Name = "cboKeyer"
        Me.cboKeyer.Size = New System.Drawing.Size(137, 21)
        Me.cboKeyer.TabIndex = 25
        '
        'Label15
        '
        Me.Label15.AutoSize = True
        Me.Label15.Location = New System.Drawing.Point(3, 264)
        Me.Label15.Name = "Label15"
        Me.Label15.Size = New System.Drawing.Size(54, 13)
        Me.Label15.TabIndex = 26
        Me.Label15.Text = "Band End"
        '
        'cboBandEnd
        '
        Me.cboBandEnd.Dock = System.Windows.Forms.DockStyle.Fill
        Me.cboBandEnd.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboBandEnd.FormattingEnabled = True
        Me.cboBandEnd.Items.AddRange(New Object() {"Stop tuning", "Wrap around"})
        Me.cboBandEnd.Location = New System.Drawing.Point(145, 267)
        Me.cboBandEnd.Name = "cboBandEnd"
        Me.cboBandEnd.Size = New System.Drawing.Size(137, 21)
        Me.cboBandEnd.TabIndex = 27
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(3, 144)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(79, 13)
        Me.Label5.TabIndex = 11
        Me.Label5.Text = "Signal Strength"
        '
        'lblSMeter
        '
        Me.lblSMeter.AutoSize = True
        Me.lblSMeter.Location = New System.Drawing.Point(145, 144)
        Me.lblSMeter.Name = "lblSMeter"
        Me.lblSMeter.Size = New System.Drawing.Size(39, 13)
        Me.lblSMeter.TabIndex = 12
        Me.lblSMeter.Text = "Label6"
        '
        'lblOutputPower
        '
        Me.lblOutputPower.AutoSize = True
        Me.lblOutputPower.Location = New System.Drawing.Point(145, 120)
        Me.lblOutputPower.Name = "lblOutputPower"
        Me.lblOutputPower.Size = New System.Drawing.Size(39, 13)
        Me.lblOutputPower.TabIndex = 10
        Me.lblOutputPower.Text = "Label5"
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(3, 120)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(72, 13)
        Me.Label4.TabIndex = 9
        Me.Label4.Text = "Output Power"
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(3, 96)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(70, 13)
        Me.Label3.TabIndex = 7
        Me.Label3.Text = "Input Voltage"
        '
        'lblVoltage
        '
        Me.lblVoltage.AutoSize = True
        Me.lblVoltage.Location = New System.Drawing.Point(145, 96)
        Me.lblVoltage.Name = "lblVoltage"
        Me.lblVoltage.Size = New System.Drawing.Size(39, 13)
        Me.lblVoltage.TabIndex = 8
        Me.lblVoltage.Text = "Label4"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(3, 72)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(75, 13)
        Me.Label2.TabIndex = 6
        Me.Label2.Text = "RX Frequency"
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(3, 48)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(74, 13)
        Me.Label1.TabIndex = 5
        Me.Label1.Text = "TX Frequency"
        '
        'Label17
        '
        Me.Label17.AutoSize = True
        Me.Label17.Location = New System.Drawing.Point(3, 0)
        Me.Label17.Name = "Label17"
        Me.Label17.Size = New System.Drawing.Size(55, 13)
        Me.Label17.TabIndex = 28
        Me.Label17.Text = "Serial Port"
        '
        'cboComPort
        '
        Me.cboComPort.Dock = System.Windows.Forms.DockStyle.Fill
        Me.cboComPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboComPort.FormattingEnabled = True
        Me.cboComPort.Location = New System.Drawing.Point(145, 3)
        Me.cboComPort.Name = "cboComPort"
        Me.cboComPort.Size = New System.Drawing.Size(137, 21)
        Me.cboComPort.TabIndex = 29
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(3, 48)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(64, 13)
        Me.Label6.TabIndex = 13
        Me.Label6.Text = "Keyer WPM"
        '
        'lblKeyerWPM
        '
        Me.lblKeyerWPM.AutoSize = True
        Me.lblKeyerWPM.Location = New System.Drawing.Point(124, 48)
        Me.lblKeyerWPM.Name = "lblKeyerWPM"
        Me.lblKeyerWPM.Size = New System.Drawing.Size(59, 13)
        Me.lblKeyerWPM.TabIndex = 17
        Me.lblKeyerWPM.TabStop = True
        Me.lblKeyerWPM.Text = "LinkLabel1"
        '
        'TextBox2
        '
        Me.TextBox2.Location = New System.Drawing.Point(3, 75)
        Me.TextBox2.Name = "TextBox2"
        Me.TextBox2.Size = New System.Drawing.Size(100, 20)
        Me.TextBox2.TabIndex = 18
        '
        'TableLayoutPanel2
        '
        Me.TableLayoutPanel2.ColumnCount = 2
        Me.TableLayoutPanel2.ColumnStyles.Add(New System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50.0!))
        Me.TableLayoutPanel2.ColumnStyles.Add(New System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50.0!))
        Me.TableLayoutPanel2.Controls.Add(Me.chkDecoder, 0, 1)
        Me.TableLayoutPanel2.Controls.Add(Me.hscDecodeThreshhold, 1, 1)
        Me.TableLayoutPanel2.Controls.Add(Me.lblKeyerWPM, 1, 2)
        Me.TableLayoutPanel2.Controls.Add(Me.Label6, 0, 2)
        Me.TableLayoutPanel2.Controls.Add(Me.TextBox2, 0, 3)
        Me.TableLayoutPanel2.Controls.Add(Me.Label16, 0, 0)
        Me.TableLayoutPanel2.Controls.Add(Me.lblCWStrength, 1, 0)
        Me.TableLayoutPanel2.Location = New System.Drawing.Point(303, 156)
        Me.TableLayoutPanel2.Name = "TableLayoutPanel2"
        Me.TableLayoutPanel2.RowCount = 5
        Me.TableLayoutPanel2.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel2.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel2.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel2.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel2.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel2.Size = New System.Drawing.Size(243, 133)
        Me.TableLayoutPanel2.TabIndex = 8
        '
        'chkDecoder
        '
        Me.chkDecoder.AutoSize = True
        Me.chkDecoder.Location = New System.Drawing.Point(3, 27)
        Me.chkDecoder.Name = "chkDecoder"
        Me.chkDecoder.Size = New System.Drawing.Size(99, 17)
        Me.chkDecoder.TabIndex = 2
        Me.chkDecoder.Text = "Morse Decoder"
        Me.chkDecoder.UseVisualStyleBackColor = True
        '
        'hscDecodeThreshhold
        '
        Me.hscDecodeThreshhold.Dock = System.Windows.Forms.DockStyle.Top
        Me.hscDecodeThreshhold.Location = New System.Drawing.Point(121, 24)
        Me.hscDecodeThreshhold.Maximum = 1023
        Me.hscDecodeThreshhold.Name = "hscDecodeThreshhold"
        Me.hscDecodeThreshhold.Size = New System.Drawing.Size(122, 17)
        Me.hscDecodeThreshhold.TabIndex = 3
        '
        'Label16
        '
        Me.Label16.AutoSize = True
        Me.Label16.Location = New System.Drawing.Point(3, 0)
        Me.Label16.Name = "Label16"
        Me.Label16.Size = New System.Drawing.Size(68, 13)
        Me.Label16.TabIndex = 19
        Me.Label16.Text = "CW Strength"
        '
        'lblCWStrength
        '
        Me.lblCWStrength.AutoSize = True
        Me.lblCWStrength.Location = New System.Drawing.Point(124, 0)
        Me.lblCWStrength.Name = "lblCWStrength"
        Me.lblCWStrength.Size = New System.Drawing.Size(45, 13)
        Me.lblCWStrength.TabIndex = 20
        Me.lblCWStrength.Text = "Label17"
        '
        'Label10
        '
        Me.Label10.AutoSize = True
        Me.Label10.Location = New System.Drawing.Point(3, 0)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(34, 13)
        Me.Label10.TabIndex = 4
        Me.Label10.Text = "Mode"
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.TableLayoutPanel3)
        Me.GroupBox1.Location = New System.Drawing.Point(303, 303)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(243, 157)
        Me.GroupBox1.TabIndex = 9
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Band Scan"
        '
        'TableLayoutPanel3
        '
        Me.TableLayoutPanel3.ColumnCount = 2
        Me.TableLayoutPanel3.ColumnStyles.Add(New System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50.0!))
        Me.TableLayoutPanel3.ColumnStyles.Add(New System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50.0!))
        Me.TableLayoutPanel3.Controls.Add(Me.cboBandscan, 1, 0)
        Me.TableLayoutPanel3.Controls.Add(Me.Label10, 0, 0)
        Me.TableLayoutPanel3.Controls.Add(Me.Label11, 0, 1)
        Me.TableLayoutPanel3.Controls.Add(Me.Label12, 0, 2)
        Me.TableLayoutPanel3.Controls.Add(Me.Label13, 0, 3)
        Me.TableLayoutPanel3.Controls.Add(Me.Label14, 0, 4)
        Me.TableLayoutPanel3.Controls.Add(Me.lblBandscanBottom, 1, 1)
        Me.TableLayoutPanel3.Controls.Add(Me.lblBandscanTop, 1, 2)
        Me.TableLayoutPanel3.Controls.Add(Me.lblBandscanWidth, 1, 3)
        Me.TableLayoutPanel3.Controls.Add(Me.lblBandscanInterval, 1, 4)
        Me.TableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill
        Me.TableLayoutPanel3.Location = New System.Drawing.Point(3, 16)
        Me.TableLayoutPanel3.Name = "TableLayoutPanel3"
        Me.TableLayoutPanel3.RowCount = 6
        Me.TableLayoutPanel3.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel3.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel3.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel3.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel3.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel3.RowStyles.Add(New System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 24.0!))
        Me.TableLayoutPanel3.Size = New System.Drawing.Size(237, 138)
        Me.TableLayoutPanel3.TabIndex = 0
        '
        'cboBandscan
        '
        Me.cboBandscan.Dock = System.Windows.Forms.DockStyle.Top
        Me.cboBandscan.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList
        Me.cboBandscan.FormattingEnabled = True
        Me.cboBandscan.Items.AddRange(New Object() {"Disabled", "Full Band", "Centered", "Custom"})
        Me.cboBandscan.Location = New System.Drawing.Point(121, 3)
        Me.cboBandscan.Name = "cboBandscan"
        Me.cboBandscan.Size = New System.Drawing.Size(113, 21)
        Me.cboBandscan.TabIndex = 6
        '
        'Label11
        '
        Me.Label11.AutoSize = True
        Me.Label11.Location = New System.Drawing.Point(3, 24)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(71, 13)
        Me.Label11.TabIndex = 7
        Me.Label11.Text = "Bottom (MHz)"
        '
        'Label12
        '
        Me.Label12.AutoSize = True
        Me.Label12.Location = New System.Drawing.Point(3, 48)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(57, 13)
        Me.Label12.TabIndex = 8
        Me.Label12.Text = "Top (MHz)"
        '
        'Label13
        '
        Me.Label13.AutoSize = True
        Me.Label13.Location = New System.Drawing.Point(3, 72)
        Me.Label13.Name = "Label13"
        Me.Label13.Size = New System.Drawing.Size(57, 13)
        Me.Label13.TabIndex = 9
        Me.Label13.Text = "Width (Hz)"
        '
        'Label14
        '
        Me.Label14.AutoSize = True
        Me.Label14.Location = New System.Drawing.Point(3, 96)
        Me.Label14.Name = "Label14"
        Me.Label14.Size = New System.Drawing.Size(64, 13)
        Me.Label14.TabIndex = 10
        Me.Label14.Text = "Interval (ms)"
        '
        'lblBandscanBottom
        '
        Me.lblBandscanBottom.Anchor = System.Windows.Forms.AnchorStyles.Left
        Me.lblBandscanBottom.AutoSize = True
        Me.lblBandscanBottom.Location = New System.Drawing.Point(121, 29)
        Me.lblBandscanBottom.Name = "lblBandscanBottom"
        Me.lblBandscanBottom.Size = New System.Drawing.Size(59, 13)
        Me.lblBandscanBottom.TabIndex = 11
        Me.lblBandscanBottom.TabStop = True
        Me.lblBandscanBottom.Text = "LinkLabel1"
        '
        'lblBandscanTop
        '
        Me.lblBandscanTop.Anchor = System.Windows.Forms.AnchorStyles.Left
        Me.lblBandscanTop.AutoSize = True
        Me.lblBandscanTop.Location = New System.Drawing.Point(121, 53)
        Me.lblBandscanTop.Name = "lblBandscanTop"
        Me.lblBandscanTop.Size = New System.Drawing.Size(59, 13)
        Me.lblBandscanTop.TabIndex = 12
        Me.lblBandscanTop.TabStop = True
        Me.lblBandscanTop.Text = "LinkLabel2"
        '
        'lblBandscanWidth
        '
        Me.lblBandscanWidth.Anchor = System.Windows.Forms.AnchorStyles.Left
        Me.lblBandscanWidth.AutoSize = True
        Me.lblBandscanWidth.Location = New System.Drawing.Point(121, 77)
        Me.lblBandscanWidth.Name = "lblBandscanWidth"
        Me.lblBandscanWidth.Size = New System.Drawing.Size(59, 13)
        Me.lblBandscanWidth.TabIndex = 13
        Me.lblBandscanWidth.TabStop = True
        Me.lblBandscanWidth.Text = "LinkLabel3"
        '
        'lblBandscanInterval
        '
        Me.lblBandscanInterval.Anchor = System.Windows.Forms.AnchorStyles.Left
        Me.lblBandscanInterval.AutoSize = True
        Me.lblBandscanInterval.Location = New System.Drawing.Point(121, 101)
        Me.lblBandscanInterval.Name = "lblBandscanInterval"
        Me.lblBandscanInterval.Size = New System.Drawing.Size(59, 13)
        Me.lblBandscanInterval.TabIndex = 14
        Me.lblBandscanInterval.TabStop = True
        Me.lblBandscanInterval.Text = "LinkLabel4"
        '
        'picBandscan
        '
        Me.picBandscan.BackColor = System.Drawing.Color.Black
        Me.picBandscan.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D
        Me.picBandscan.Location = New System.Drawing.Point(552, 12)
        Me.picBandscan.Name = "picBandscan"
        Me.picBandscan.Size = New System.Drawing.Size(231, 115)
        Me.picBandscan.TabIndex = 10
        Me.picBandscan.TabStop = False
        '
        'frmMain
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(795, 516)
        Me.Controls.Add(Me.picBandscan)
        Me.Controls.Add(Me.GroupBox1)
        Me.Controls.Add(Me.TableLayoutPanel2)
        Me.Controls.Add(Me.TableLayoutPanel1)
        Me.Controls.Add(Me.CheckBox1)
        Me.Controls.Add(Me.TextBox1)
        Me.Name = "frmMain"
        Me.Text = "Form1"
        Me.TableLayoutPanel1.ResumeLayout(False)
        Me.TableLayoutPanel1.PerformLayout()
        Me.TableLayoutPanel2.ResumeLayout(False)
        Me.TableLayoutPanel2.PerformLayout()
        Me.GroupBox1.ResumeLayout(False)
        Me.TableLayoutPanel3.ResumeLayout(False)
        Me.TableLayoutPanel3.PerformLayout()
        CType(Me.picBandscan, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents SerialPort1 As System.IO.Ports.SerialPort
    Friend WithEvents TextBox1 As System.Windows.Forms.TextBox
    Friend WithEvents CheckBox1 As System.Windows.Forms.CheckBox
    Friend WithEvents lblFrequency As System.Windows.Forms.Label
    Friend WithEvents lblRxFrequency As System.Windows.Forms.Label
    Friend WithEvents TableLayoutPanel1 As System.Windows.Forms.TableLayoutPanel
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents lblVoltage As System.Windows.Forms.Label
    Friend WithEvents Label4 As System.Windows.Forms.Label
    Friend WithEvents lblOutputPower As System.Windows.Forms.Label
    Friend WithEvents Label5 As System.Windows.Forms.Label
    Friend WithEvents lblSMeter As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents cmdTuneDown As System.Windows.Forms.Button
    Friend WithEvents cmdTuneUp As System.Windows.Forms.Button
    Friend WithEvents lblKeyerWPM As System.Windows.Forms.LinkLabel
    Friend WithEvents TextBox2 As System.Windows.Forms.TextBox
    Friend WithEvents cmdSetFrequency As System.Windows.Forms.Button
    Friend WithEvents TableLayoutPanel2 As System.Windows.Forms.TableLayoutPanel
    Friend WithEvents chkPortOpen As System.Windows.Forms.CheckBox
    Friend WithEvents cmdReset As System.Windows.Forms.Button
    Friend WithEvents cboBandwidth As System.Windows.Forms.ComboBox
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents cboTuneStep As System.Windows.Forms.ComboBox
    Friend WithEvents Label9 As System.Windows.Forms.Label
    Friend WithEvents cboKeyer As System.Windows.Forms.ComboBox
    Friend WithEvents chkDecoder As System.Windows.Forms.CheckBox
    Friend WithEvents hscDecodeThreshhold As System.Windows.Forms.HScrollBar
    Friend WithEvents Label10 As System.Windows.Forms.Label
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents TableLayoutPanel3 As System.Windows.Forms.TableLayoutPanel
    Friend WithEvents cboBandscan As System.Windows.Forms.ComboBox
    Friend WithEvents Label11 As System.Windows.Forms.Label
    Friend WithEvents Label12 As System.Windows.Forms.Label
    Friend WithEvents Label13 As System.Windows.Forms.Label
    Friend WithEvents Label14 As System.Windows.Forms.Label
    Friend WithEvents lblBandscanBottom As System.Windows.Forms.LinkLabel
    Friend WithEvents lblBandscanTop As System.Windows.Forms.LinkLabel
    Friend WithEvents lblBandscanWidth As System.Windows.Forms.LinkLabel
    Friend WithEvents lblBandscanInterval As System.Windows.Forms.LinkLabel
    Friend WithEvents picBandscan As System.Windows.Forms.PictureBox
    Friend WithEvents Label15 As System.Windows.Forms.Label
    Friend WithEvents cboBandEnd As System.Windows.Forms.ComboBox
    Friend WithEvents Label16 As System.Windows.Forms.Label
    Friend WithEvents lblCWStrength As System.Windows.Forms.Label
    Friend WithEvents Label17 As System.Windows.Forms.Label
    Friend WithEvents cboComPort As System.Windows.Forms.ComboBox

End Class
