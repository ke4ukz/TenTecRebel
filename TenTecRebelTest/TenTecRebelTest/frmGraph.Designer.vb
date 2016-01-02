<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmGraph
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
        Me.picGraph = New System.Windows.Forms.PictureBox()
        CType(Me.picGraph, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'picGraph
        '
        Me.picGraph.BackColor = System.Drawing.Color.Black
        Me.picGraph.Dock = System.Windows.Forms.DockStyle.Fill
        Me.picGraph.Location = New System.Drawing.Point(0, 0)
        Me.picGraph.Name = "picGraph"
        Me.picGraph.Size = New System.Drawing.Size(703, 353)
        Me.picGraph.TabIndex = 0
        Me.picGraph.TabStop = False
        '
        'frmGraph
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(703, 353)
        Me.Controls.Add(Me.picGraph)
        Me.Name = "frmGraph"
        Me.Text = "frmGraph"
        CType(Me.picGraph, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents picGraph As System.Windows.Forms.PictureBox
End Class
