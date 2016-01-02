Public Class frmMain

    Private Const DATAHEADER As Byte = &HEE
    Private Const DATAFOOTER As Byte = &HFF

    Private SerialDataTypes As New Dictionary(Of String, Byte)
    Private BandscanData(255) As Byte
    Public SMeterGraph() As Integer
    Public CWReadGraph() As Integer
    Public SMeterIndex As Integer = 0
    Public CWReadIndex As Integer = 0

    Private Enum SerialCommands As Byte
        SetFrequency = &H80
        TuneUp = &H81
        TuneDown = &H82
        SetKeyerWPM = &H83
        SendChar = &H84
        SetBandwidth = &H85
        SetStepSize = &H86
        SetUser = &H87
        SetKeyerOnOff = &H88
        SetDecoderOnOff = &H89
        SetDecodeThreshhold = &H8A
        SetBandscanMode = &H8B
        SetBandscanWidth = &H8C
        SetBandscanTop = &H8D
        SetBandscanBottom = &H8E
        SetBandscanInterval = &H8F
        SetWraparound = &H90
    End Enum

    Private Delegate Sub ReceivedStringCallback(ByVal Received As String)
    Private Delegate Sub TransmittingCallback(ByVal TX As Boolean)
    Private Delegate Sub ReceivedVoltageCallback(ByVal ReadVoltage As UInt32)
    Private Delegate Sub ReceivedTXFrequencyCallback(ByVal CurrentTXFrequency As UInt32)
    Private Delegate Sub ReceivedRXFrequencyCallback(ByVal CurrentRXFrequency As UInt32)
    Private Delegate Sub ReceivedOutputPowerCallback(ByVal CurrentOutputPower As UInt32)
    Private Delegate Sub ReceivedSignalStrengthCallback(ByVal CurrentSignalStrength As UInt32)
    Private Delegate Sub ReceivedKeyerWPMCallback(ByVal CurrentKeyerWPM As UInt32)
    Private Delegate Sub ReceivedCharacterSentCallback()
    Private Delegate Sub ReceivedBandwidthCallback(ByVal CurrentBandwidth As UInt32)
    Private Delegate Sub ReceivedTuneStepCallback(ByVal CurrentTuneStep As UInt32)
    Private Delegate Sub ReceivedKeyerOnOffCallback(ByVal CurrentKeyerOnOff As UInt32)
    Private Delegate Sub ReceivedDecoderOnOffCallback(ByVal CurrentDecoderOnOff As UInt32)
    Private Delegate Sub ReceivedDecodeThreshholdCallback(ByVal CurrentThreshhold As UInt32)
    Private Delegate Sub ReceivedBandscanDataCallback(ByRef BandscanData() As Byte)
    Private Delegate Sub ReceivedBandscanInfoCallback(ByVal BandscanSetting As SerialCommands, ByVal NewValue As UInt32)
    Private Delegate Sub ReceivedWraparoundCallback(ByVal Wraparound As UInt32)
    Private Delegate Sub ReceivedCWReadCallback(ByVal CWRead As UInt32)

    Private Enum SerialProcessingSteps As Byte
        SearchingForHeader = 0
        ExpectingType = 1
        ReadingString = 3
        Expecting1MoreByte = 4
        Expecting2MoreBytes = 5
        Expecting3MoreBytes = 6
        Expecting4MoreBytes = 7
        ReadingBandscan = 8
        ExpectingFooter = 99
    End Enum

    Private Sub LoadSerialDataTypes()
        SerialDataTypes.Add("String", &H0) 'Special method to receive a variable-length string
        SerialDataTypes.Add("TX Start", &H1) 'transmit start (no data)
        SerialDataTypes.Add("TX End", &H2) 'transmit end (no data)
        SerialDataTypes.Add("Voltage", &H3) 'data contains power supply voltage
        SerialDataTypes.Add("TX Frequency", &H4) 'data contains tx frequency
        SerialDataTypes.Add("RX Frequency", &H5) 'data contains rx frequency
        SerialDataTypes.Add("Output Power", &H6) 'data contains output power
        SerialDataTypes.Add("Signal Strength", &H7) 'data contains received signal strength
        SerialDataTypes.Add("Keyer WPM", &H8) 'data contains keyer wpm
        SerialDataTypes.Add("Received Character", &H9) 'data contains received character
        SerialDataTypes.Add("Character Sent", &HA) 'character was sent (no data)
        SerialDataTypes.Add("Bandwidth", &HB)
        SerialDataTypes.Add("Tune Step", &HC)
        SerialDataTypes.Add("User", &HD)
        SerialDataTypes.Add("Keyer OnOff", &HE)
        SerialDataTypes.Add("Initialization Finished", &HF)
        SerialDataTypes.Add("Decoder OnOff", &H10)
        SerialDataTypes.Add("Decode Threshhold", &H11)
        SerialDataTypes.Add("Bandscan Mode", &H13)
        SerialDataTypes.Add("Bandscan Width", &H14)
        SerialDataTypes.Add("Bandscan Top", &H15)
        SerialDataTypes.Add("Bandscan Bottom", &H16)
        SerialDataTypes.Add("Bandscan Interval", &H17)
        SerialDataTypes.Add("Bandscan Data", &H18)
        SerialDataTypes.Add("Wraparound Tuning", &H19)
        SerialDataTypes.Add("CW Read", &H1A)
    End Sub

    Private Sub ReceivedString(ByVal Received As String)
        If Me.InvokeRequired Then
            Dim d As New ReceivedStringCallback(AddressOf ReceivedString)
            Me.BeginInvoke(d, New Object() {Received})
        Else
            TextBox1.AppendText(Received)
        End If
    End Sub

    Private Sub Transmitting(ByVal TX As Boolean)
        If Me.InvokeRequired Then
            Dim d As New TransmittingCallback(AddressOf Transmitting)
            Me.BeginInvoke(d, New Object() {TX})
        Else
            CheckBox1.Checked = TX
        End If
    End Sub

    Private Sub ReceivedVoltage(ByVal ReadVoltage As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedVoltageCallback(AddressOf ReceivedVoltage)
            Me.BeginInvoke(d, New Object() {ReadVoltage})
        Else
            lblVoltage.Text = (ReadVoltage * 0.01611328125).ToString("00.00")
        End If
    End Sub

    Private Sub ReceivedTXFrequency(ByVal CurrentTXFrequency As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedTXFrequencyCallback(AddressOf ReceivedTXFrequency)
            Me.BeginInvoke(d, New Object() {CurrentTXFrequency})
        Else
            lblFrequency.Text = (CurrentTXFrequency / 1000000.0).ToString("#0.000 000")
        End If
    End Sub

    Private Sub ReceivedRXFrequency(ByVal CurrentRXFrequency As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedTXFrequencyCallback(AddressOf ReceivedRXFrequency)
            Me.BeginInvoke(d, New Object() {CurrentRXFrequency})
        Else
            lblRxFrequency.Text = (CurrentRXFrequency / 1000000.0).ToString("#0.000 000")
        End If
    End Sub

    Private Sub ReceivedOutputPower(ByVal CurrentOutputPower As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedOutputPowerCallback(AddressOf ReceivedOutputPower)
            Me.BeginInvoke(d, New Object() {CurrentOutputPower})
        Else
            'p = ie
            'e = ir
            '
            'r = 52
            'e = (CurrentOutputPower / 1024) * 3.3
            'e = CurrentOutputPower * 0.00322265625
            'i = e/r
            'i = (CurrentOutputPower * 0.00322265625) / 52
            'i = CurrentOutputPower * 6.1974158653846153846153846153846e-5
            'p = CurrentOutputPower * 6.1974158653846153846153846153846e-5 * CurrentOutputPower * 0.00322265625
            'p = CurrentOutputPower ^ 2 * 1.9972140972430889423076923076923e-7
            'lblOutputPower.Text = ((CurrentOutputPower ^ 2) * 0.0000001997214097243089).ToString()
            lblOutputPower.Text = CurrentOutputPower.ToString()
        End If
    End Sub

    Private Sub ReceivedSignalStrength(ByVal CurrentSignalStrength As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedSignalStrengthCallback(AddressOf ReceivedSignalStrength)
            Me.BeginInvoke(d, New Object() {CurrentSignalStrength})
        Else
            lblSMeter.Text = CurrentSignalStrength.ToString
            SMeterGraph(SMeterIndex) = CInt(CurrentSignalStrength)
            SMeterIndex += 1
            If (SMeterIndex >= SMeterGraph.Length) Then SMeterIndex = 0
            frmGraph.picGraph.Invalidate()
        End If
    End Sub

    Private Sub ReceivedKeyerWPM(ByVal CurrentKeyerWPM As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedKeyerWPMCallback(AddressOf ReceivedKeyerWPM)
            Me.BeginInvoke(d, New Object() {CurrentKeyerWPM})
        Else
            lblKeyerWPM.Text = CurrentKeyerWPM.ToString
        End If
    End Sub

    Private Sub ReceivedCharacterSent()
        If Me.InvokeRequired Then
            Dim d As New ReceivedCharacterSentCallback(AddressOf ReceivedCharacterSent)
            Me.BeginInvoke(d)
        Else
            TextBox2.ReadOnly = False
            TextBox2.Focus()
        End If
    End Sub

    Private Sub ReceivedBandwidth(ByVal CurrentBandwith As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedBandwidthCallback(AddressOf ReceivedBandwidth)
            Me.BeginInvoke(d, New Object() {CurrentBandwith})
        Else
            If cboBandwidth.SelectedIndex <> CInt(CurrentBandwith) Then
                cboBandwidth.SelectedIndex = CInt(CurrentBandwith)
            End If
        End If
    End Sub

    Private Sub ReceivedTuneStep(ByVal CurrentTuneStep As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedTuneStepCallback(AddressOf ReceivedTuneStep)
            Me.BeginInvoke(d, New Object() {CurrentTuneStep})
        Else
            If cboTuneStep.SelectedIndex <> CInt(CurrentTuneStep) Then
                cboTuneStep.SelectedIndex = CInt(CurrentTuneStep)
            End If
        End If
    End Sub

    Private Sub ReceivedKeyerOnOff(ByVal CurrentKeyerOnOff As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedKeyerOnOffCallback(AddressOf ReceivedKeyerOnOff)
            Me.BeginInvoke(d, New Object() {CurrentKeyerOnOff})
        Else
            cboKeyer.SelectedIndex = CInt(CurrentKeyerOnOff)
        End If
    End Sub

    Private Sub ReceivedDecoderOnOff(ByVal CurrentDecoderOnOff As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedDecoderOnOffCallback(AddressOf ReceivedDecoderOnOff)
            Me.BeginInvoke(d, New Object() {CurrentDecoderOnOff})
        Else
            If CurrentDecoderOnOff = 0 Then
                chkDecoder.Checked = False
            Else
                chkDecoder.Checked = True
            End If
        End If
    End Sub

    Private Sub ReceivedDecodeThreshhold(ByVal CurrentThreshhold As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedDecodeThreshholdCallback(AddressOf ReceivedDecodeThreshhold)
            Me.BeginInvoke(d, New Object() {CurrentThreshhold})
        Else
            hscDecodeThreshhold.Value = CInt(CurrentThreshhold)
        End If
    End Sub

    Private Sub ReceivedBandscanData(ByRef newBandscanData() As Byte)
        If Me.InvokeRequired Then
            Dim d As New ReceivedBandscanDataCallback(AddressOf ReceivedBandscanData)
            Me.BeginInvoke(d, New Object() {newBandscanData})
        Else
            For I As Integer = 0 To BandscanData.Length - 1
                BandscanData(I) = newBandscanData(I)
                Console.Write(Hex(BandscanData(I)))
            Next
            Console.WriteLine()
            picBandscan.Invalidate()
        End If
    End Sub

    Private Sub ReceivedBandscanInfo(ByVal BandscanSetting As SerialCommands, ByVal NewValue As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedBandscanInfoCallback(AddressOf ReceivedBandscanInfo)
            Me.BeginInvoke(d, New Object() {BandscanSetting, NewValue})
        Else
            Select Case BandscanSetting
                Case SerialCommands.SetBandscanBottom
                    lblBandscanBottom.Text = NewValue.ToString
                Case SerialCommands.SetBandscanInterval
                    lblBandscanInterval.Text = NewValue.ToString
                Case SerialCommands.SetBandscanTop
                    lblBandscanTop.Text = NewValue.ToString
                Case SerialCommands.SetBandscanWidth
                    lblBandscanWidth.Text = NewValue.ToString
                Case SerialCommands.SetBandscanMode
                    cboBandscan.SelectedIndex = CInt(NewValue)
            End Select
        End If
    End Sub

    Private Sub ReceivedWraparound(ByVal Wraparound As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedWraparoundCallback(AddressOf ReceivedWraparound)
            Me.BeginInvoke(d, New Object() {Wraparound})
        Else
            cboBandEnd.SelectedIndex = CInt(Wraparound)
        End If
    End Sub

    Private Sub ReceivedCWRead(ByVal CWRead As UInt32)
        If Me.InvokeRequired Then
            Dim d As New ReceivedCWReadCallback(AddressOf ReceivedCWRead)
            Me.BeginInvoke(d, New Object() {CWRead})
        Else
            lblCWStrength.Text = CInt(CWRead).ToString
            CWReadGraph(CWReadIndex) = CInt(CWRead)
            CWReadIndex += 1
            If (CWReadIndex >= CWReadGraph.Length) Then CWReadIndex = 0
            frmGraph.picGraph.Invalidate()
        End If
    End Sub

    Private Function BytesToInt(ByRef Bytes() As Byte) As UInt32
        Dim Shift As Integer
        Dim Ret As UInt32 = 0
        For I As Integer = 0 To Bytes.Length - 1
            Shift = 8 * (Bytes.Length - I - 1)
            Ret = Ret Or (CType(Bytes(I), UInt32) << Shift)
        Next
        Return Ret
    End Function

    Private Function SendCommand(ByVal Command As SerialCommands) As Boolean
        If SerialPort1.IsOpen() Then
            Dim out(2) As Byte
            out(0) = DATAHEADER
            out(1) = Command
            out(2) = DATAFOOTER
            SerialPort1.Write(out, 0, 3)
            Return True
        Else
            Return False
        End If
    End Function

    Private Function SendCommand(ByVal Command As SerialCommands, ByVal Data As Object) As Boolean
        If SerialPort1.IsOpen() Then
            Dim out(6) As Byte
            Dim d As UInt32 = CType(Data, UInt32)
            out(0) = DATAHEADER
            out(1) = Command
            out(2) = CByte((d And &HFF000000) >> 24)
            out(3) = CByte((d And &HFF0000) >> 16)
            out(4) = CByte((d And &HFF00) >> 8)
            out(5) = CByte(d And &HFF)
            out(6) = DATAFOOTER
            SerialPort1.Write(out, 0, 7)
            Return True
        Else
            Return False
        End If
    End Function

    Private Sub Form1_FormClosing(sender As Object, e As FormClosingEventArgs) Handles Me.FormClosing
        If SerialPort1.IsOpen Then
            SerialPort1.DiscardInBuffer()
            SerialPort1.Close()
        End If
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        LoadSerialDataTypes()
        cboBandwidth.SelectedIndex = 0
        cboTuneStep.SelectedIndex = 0
        cboKeyer.SelectedIndex = 0
        cboBandscan.SelectedIndex = 0
        frmGraph.Show()
        ReDim SMeterGraph(frmGraph.picGraph.Width)
        ReDim CWReadGraph(frmGraph.picGraph.Width)
    End Sub

    Private Sub SerialPort1_DataReceived(sender As Object, e As IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        Static CurrentSearchStep As SerialProcessingSteps = SerialProcessingSteps.SearchingForHeader
        Static CurrentDataType As Byte
        Static IncomingString As System.Text.StringBuilder
        Static IncomingBytes(3) As Byte
        Static BandscanData(255) As Byte
        Static BandscanDataIndex As Integer = 0

        Dim NextByte As Byte
        While SerialPort1.IsOpen AndAlso SerialPort1.BytesToRead > 0
            Try
                NextByte = CByte(SerialPort1.ReadByte())
                'Console.Write(Hex(NextByte) & " ")
                Select Case CurrentSearchStep
                    Case SerialProcessingSteps.SearchingForHeader
                        If NextByte = DATAHEADER Then
                            CurrentSearchStep = SerialProcessingSteps.ExpectingType
                        Else
                            CurrentSearchStep = SerialProcessingSteps.SearchingForHeader
                        End If
                    Case SerialProcessingSteps.ExpectingType
                        If SerialDataTypes.ContainsValue(NextByte) Then
                            CurrentDataType = NextByte
                            Select Case CurrentDataType
                                Case SerialDataTypes("String")
                                    CurrentSearchStep = SerialProcessingSteps.ReadingString
                                    IncomingString = New System.Text.StringBuilder
                                Case SerialDataTypes("TX Start"), SerialDataTypes("TX End"), SerialDataTypes("Character Sent"), _
                                     SerialDataTypes("Initialization Finished")
                                    CurrentSearchStep = SerialProcessingSteps.ExpectingFooter
                                Case SerialDataTypes("Voltage"), SerialDataTypes("TX Frequency"), SerialDataTypes("RX Frequency"), _
                                     SerialDataTypes("Output Power"), SerialDataTypes("Signal Strength"), SerialDataTypes("Keyer WPM"), _
                                     SerialDataTypes("Bandwidth"), SerialDataTypes("Tune Step"), SerialDataTypes("User"), _
                                     SerialDataTypes("Keyer OnOff"), SerialDataTypes("Decoder OnOff"), SerialDataTypes("Decode Threshhold"), _
                                     SerialDataTypes("Received Character"), SerialDataTypes("Bandscan Mode"), SerialDataTypes("Bandscan Width"), _
                                     SerialDataTypes("Bandscan Top"), SerialDataTypes("Bandscan Bottom"), SerialDataTypes("Bandscan Interval"), _
                                     SerialDataTypes("Wraparound Tuning"), SerialDataTypes("CW Read")
                                    CurrentSearchStep = SerialProcessingSteps.Expecting4MoreBytes
                                Case SerialDataTypes("Bandscan Data")
                                    CurrentSearchStep = SerialProcessingSteps.ReadingBandscan
                                    BandscanDataIndex = 0
                            End Select
                        Else
                            CurrentSearchStep = SerialProcessingSteps.SearchingForHeader
                        End If
                    Case SerialProcessingSteps.ReadingString
                        If (NextByte <> DATAFOOTER) Then
                            IncomingString.Append(Chr(NextByte))
                        Else
                            ReceivedString(IncomingString.ToString)
                            IncomingString = Nothing
                            CurrentSearchStep = SerialProcessingSteps.SearchingForHeader
                        End If
                    Case SerialProcessingSteps.ExpectingFooter
                        If (NextByte = DATAFOOTER) Then
                            'Found footer
                            Select Case CurrentDataType
                                Case SerialDataTypes("Voltage")
                                    ReceivedVoltage(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("TX Frequency")
                                    ReceivedTXFrequency(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("RX Frequency")
                                    ReceivedRXFrequency(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Output Power")
                                    ReceivedOutputPower(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Signal Strength")
                                    ReceivedSignalStrength(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Keyer WPM")
                                    ReceivedKeyerWPM(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("TX Start")
                                    Transmitting(True)
                                Case SerialDataTypes("TX End")
                                    Transmitting(False)
                                Case SerialDataTypes("Character Sent")
                                    ReceivedCharacterSent()
                                Case SerialDataTypes("Bandwidth")
                                    ReceivedBandwidth(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Tune Step")
                                    ReceivedTuneStep(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Keyer OnOff")
                                    ReceivedKeyerOnOff(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Initialization Finished")
                                    ReceivedString("Initialization finished" + ControlChars.CrLf)
                                Case SerialDataTypes("Decoder OnOff")
                                    ReceivedDecoderOnOff(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Decode Threshhold")
                                    ReceivedDecodeThreshhold(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Received Character")
                                    ReceivedString(Chr(CInt(BytesToInt(IncomingBytes))))
                                Case SerialDataTypes("Bandscan Data")
                                    ReceivedBandscanData(BandscanData)
                                Case SerialDataTypes("Bandscan Top")
                                    ReceivedBandscanInfo(SerialCommands.SetBandscanTop, BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Bandscan Bottom")
                                    ReceivedBandscanInfo(SerialCommands.SetBandscanBottom, BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Bandscan Width")
                                    ReceivedBandscanInfo(SerialCommands.SetBandscanWidth, BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Bandscan Interval")
                                    ReceivedBandscanInfo(SerialCommands.SetBandscanInterval, BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Bandscan Mode")
                                    ReceivedBandscanInfo(SerialCommands.SetBandscanMode, BytesToInt(IncomingBytes))
                                Case SerialDataTypes("Wraparound Tuning")
                                    ReceivedWraparound(BytesToInt(IncomingBytes))
                                Case SerialDataTypes("CW Read")
                                    receivedcwread(BytesToInt(IncomingBytes))
                            End Select
                        End If
                        CurrentSearchStep = SerialProcessingSteps.SearchingForHeader
                    Case SerialProcessingSteps.Expecting4MoreBytes
                        IncomingBytes(0) = NextByte
                        CurrentSearchStep = SerialProcessingSteps.Expecting3MoreBytes
                    Case SerialProcessingSteps.Expecting3MoreBytes
                        IncomingBytes(1) = NextByte
                        CurrentSearchStep = SerialProcessingSteps.Expecting2MoreBytes
                    Case SerialProcessingSteps.Expecting2MoreBytes
                        IncomingBytes(2) = NextByte
                        CurrentSearchStep = SerialProcessingSteps.Expecting1MoreByte
                    Case SerialProcessingSteps.Expecting1MoreByte
                        IncomingBytes(3) = NextByte
                        CurrentSearchStep = SerialProcessingSteps.ExpectingFooter
                    Case SerialProcessingSteps.ReadingBandscan
                        BandscanData(BandscanDataIndex) = NextByte
                        BandscanDataIndex += 1
                        If BandscanDataIndex >= BandscanData.Length Then
                            CurrentSearchStep = SerialProcessingSteps.ExpectingFooter
                        End If
                End Select
            Catch ex As Exception
                Exit While
            End Try
        End While
    End Sub

    Private Sub cmdTuneDown_Click(sender As Object, e As EventArgs) Handles cmdTuneDown.Click
        SendCommand(SerialCommands.TuneDown)
    End Sub

    Private Sub cmdTuneUp_Click(sender As Object, e As EventArgs) Handles cmdTuneUp.Click
        SendCommand(SerialCommands.TuneUp)
    End Sub

    Private Sub lblKeyerWPM_LinkClicked(sender As Object, e As LinkLabelLinkClickedEventArgs) Handles lblKeyerWPM.LinkClicked
        Dim NewWPM As String = InputBox("Enter new keyer WPM:", "Keyer WPM", lblKeyerWPM.Text)
        Dim WPM As Integer
        Integer.TryParse(NewWPM, WPM)
        If WPM > 0 Then
            SendCommand(SerialCommands.SetKeyerWPM, WPM)
        End If
    End Sub

    Private Sub TextBox2_KeyPress(sender As Object, e As KeyPressEventArgs) Handles TextBox2.KeyPress
        e.KeyChar = UCase(e.KeyChar)
        e.Handled = True
        If SendCommand(SerialCommands.SendChar, Asc(e.KeyChar)) Then
            TextBox2.ReadOnly = True
            TextBox2.AppendText(e.KeyChar)
        End If

    End Sub

    Private Sub cmdSetFrequency_Click(sender As Object, e As EventArgs) Handles cmdSetFrequency.Click
        Dim newFreq As String = InputBox("Enter frequency:", "Set Frequency", lblFrequency.Text)
        Dim newFreqD As Decimal
        Decimal.TryParse(newFreq, newFreqD)
        If newFreqD > 0 Then SendCommand(SerialCommands.SetFrequency, newFreqD * 1000000.0)
    End Sub

    Private Sub chkPortOpen_CheckedChanged(sender As Object, e As EventArgs) Handles chkPortOpen.CheckedChanged
        If chkPortOpen.Checked And Not SerialPort1.IsOpen Then
            SerialPort1.Open()
        ElseIf Not chkPortOpen.Checked And SerialPort1.IsOpen Then
            SerialPort1.DiscardInBuffer()
            SerialPort1.Close()
        End If
    End Sub

    Private Sub cmdReset_Click(sender As Object, e As EventArgs) Handles cmdReset.Click
        SerialPort1.DtrEnable = True
        Threading.Thread.Sleep(500)
        SerialPort1.DtrEnable = False
    End Sub

    Private Sub cboBandwidth_SelectedIndexChanged(sender As Object, e As EventArgs) Handles cboBandwidth.SelectedIndexChanged
        SendCommand(SerialCommands.SetBandwidth, cboBandwidth.SelectedIndex)
    End Sub

    Private Sub cboTuneStep_SelectedIndexChanged(sender As Object, e As EventArgs) Handles cboTuneStep.SelectedIndexChanged
        SendCommand(SerialCommands.SetStepSize, cboTuneStep.SelectedIndex)
    End Sub

    Private Sub cboKeyer_SelectedIndexChanged(sender As Object, e As EventArgs) Handles cboKeyer.SelectedIndexChanged
        SendCommand(SerialCommands.SetKeyerOnOff, cboKeyer.SelectedIndex)
        TextBox2.Enabled = (cboKeyer.SelectedIndex = 2)
    End Sub

    Private Sub chkDecoder_CheckedChanged(sender As Object, e As EventArgs) Handles chkDecoder.CheckedChanged
        SendCommand(SerialCommands.SetDecoderOnOff, IIf(chkDecoder.Checked, 1, 0))
    End Sub

    Private Sub hscDecodeThreshhold_Scroll(sender As Object, e As ScrollEventArgs) Handles hscDecodeThreshhold.Scroll
        If e.OldValue <> e.NewValue Then
            SendCommand(SerialCommands.SetDecodeThreshhold, e.NewValue)
        End If
    End Sub

    Private Sub cboBandscan_SelectedIndexChanged(sender As Object, e As EventArgs) Handles cboBandscan.SelectedIndexChanged
        Select Case cboBandscan.SelectedIndex
            Case 0 'Disabled
                lblBandscanBottom.Enabled = False
                lblBandscanTop.Enabled = False
                lblBandscanWidth.Enabled = False
                lblBandscanInterval.Enabled = False
            Case 1 'Full band
                lblBandscanBottom.Enabled = False
                lblBandscanTop.Enabled = False
                lblBandscanWidth.Enabled = False
                lblBandscanInterval.Enabled = True
            Case 2 'Centered
                lblBandscanBottom.Enabled = False
                lblBandscanTop.Enabled = False
                lblBandscanWidth.Enabled = True
                lblBandscanInterval.Enabled = True
            Case 3 'Custom
                lblBandscanBottom.Enabled = True
                lblBandscanTop.Enabled = True
                lblBandscanWidth.Enabled = False
                lblBandscanInterval.Enabled = True
        End Select
        SendCommand(SerialCommands.SetBandscanMode, cboBandscan.SelectedIndex)
    End Sub

    Private Sub lblBandscanBottom_LinkClicked(sender As Object, e As LinkLabelLinkClickedEventArgs) Handles lblBandscanBottom.LinkClicked
        Dim bsBottomS As String = InputBox("New bandscan bottom (in MHz):", "Bandscan Bottom", lblBandscanBottom.Text)
        If bsBottomS = "" Then Exit Sub
        Dim bsBottomD As Decimal
        Decimal.TryParse(bsBottomS, bsBottomD)
        SendCommand(SerialCommands.SetBandscanBottom, bsBottomD * 1000000.0)
    End Sub

    Private Sub lblBandscanTop_LinkClicked(sender As Object, e As LinkLabelLinkClickedEventArgs) Handles lblBandscanTop.LinkClicked
        Dim bsTopS As String = InputBox("New bandscan top (in MHz):", "Bandscan Top", lblBandscanTop.Text)
        If bsTopS = "" Then Exit Sub
        Dim bsTopD As Decimal
        Decimal.TryParse(bsTopS, bsTopD)
        SendCommand(SerialCommands.SetBandscanTop, bsTopD * 1000000.0)
    End Sub

    Private Sub lblBandscanWidth_LinkClicked(sender As Object, e As LinkLabelLinkClickedEventArgs) Handles lblBandscanWidth.LinkClicked
        Dim bsWidthS As String = InputBox("New bandscan width (in Hz):", "Bandscan Width", lblBandscanWidth.Text)
        If bsWidthS = "" Then Exit Sub
        Dim bsWidthD As Decimal
        Decimal.TryParse(bsWidthS, bsWidthD)
        SendCommand(SerialCommands.SetBandscanWidth, bsWidthD)
    End Sub

    Private Sub lblBandscanInterval_LinkClicked(sender As Object, e As LinkLabelLinkClickedEventArgs) Handles lblBandscanInterval.LinkClicked
        Dim bsIntervalS As String = InputBox("New bandscan interval (in ms):", "Bandscan Interval", lblBandscanInterval.Text)
        If bsIntervalS = "" Then Exit Sub
        Dim bsIntervalD As Decimal
        Decimal.TryParse(bsIntervalS, bsIntervalD)
        SendCommand(SerialCommands.SetBandscanInterval, bsIntervalD)
    End Sub

    Private Sub picBandscan_Paint(sender As Object, e As PaintEventArgs) Handles picBandscan.Paint
        Dim g As System.Drawing.Graphics = e.Graphics
        g.Clear(picBandscan.BackColor)
        If cboBandscan.SelectedIndex > 0 Then
            Dim colWidth As Single = g.ClipBounds.Width / 256
            Dim curY As Single
            For I As Integer = 0 To 255
                curY = g.ClipBounds.Height / 256 * BandscanData(I)
                g.DrawRectangle(Pens.Lime, I * colWidth, g.ClipBounds.Height - curY - 1, colWidth, curY)
            Next
        End If


    End Sub

    Private Sub cboBandEnd_SelectedIndexChanged(sender As Object, e As EventArgs) Handles cboBandEnd.SelectedIndexChanged
        SendCommand(SerialCommands.SetWraparound, cboBandEnd.SelectedIndex)
    End Sub

End Class
