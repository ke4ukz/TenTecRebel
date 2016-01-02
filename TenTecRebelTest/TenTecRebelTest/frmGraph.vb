Public Class frmGraph

    Private Sub picGraph_Paint(sender As Object, e As PaintEventArgs) Handles picGraph.Paint
        Dim g As System.Drawing.Graphics = e.Graphics
        Dim y1 As Single, y2 As Single
        g.Clear(Color.Black)
        For x As Integer = 1 To frmMain.CWReadGraph.Length - 1
            If (x <> frmMain.CWReadIndex) Then
                y1 = CSng(g.ClipBounds.Height * (1 - frmMain.CWReadGraph(x - 1) / 1024))
                y2 = CSng(g.ClipBounds.Height * (1 - frmMain.CWReadGraph(x) / 1024))
                g.DrawLine(Pens.Lime, x - 1, y1, x, y2)
            Else
                g.DrawLine(Pens.Lime, x, 0, x, g.ClipBounds.Height)
            End If

            If (x <> frmMain.SMeterIndex) Then
                y1 = CSng(g.ClipBounds.Height * (1 - frmMain.SMeterGraph(x - 1) / 1024))
                y2 = CSng(g.ClipBounds.Height * (1 - frmMain.SMeterGraph(x) / 1024))
                g.DrawLine(Pens.Yellow, x - 1, y1, x, y2)
            Else
                g.DrawLine(Pens.Yellow, x, 0, x, g.ClipBounds.Height)
            End If
        Next
    End Sub

    Private Sub picGraph_Resize(sender As Object, e As EventArgs) Handles picGraph.Resize
        If picGraph.Width > 0 Then
            ReDim frmMain.CWReadGraph(picGraph.Width)
            ReDim frmMain.SMeterGraph(picGraph.Width)
            frmMain.SMeterIndex = 0
            frmMain.CWReadIndex = 0
        End If
    End Sub
End Class