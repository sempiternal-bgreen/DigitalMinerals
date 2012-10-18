namespace Sapphire
{
    partial class SapphireForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(SapphireForm));
            this.SapphireMenu = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SapphireFileExit = new System.Windows.Forms.ToolStripMenuItem();
            this.optionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.documentationToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SapphireControl = new System.Windows.Forms.TabControl();
            this.RenderTab = new System.Windows.Forms.TabPage();
            this.RenderSubControl = new System.Windows.Forms.TabControl();
            this.PostProcessTab = new System.Windows.Forms.TabPage();
            this.PostProcessEffects = new System.Windows.Forms.GroupBox();
            this.PostProcessComboBox = new System.Windows.Forms.ComboBox();
            this.PostProcessCheckBox = new System.Windows.Forms.CheckBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.LevelTab = new System.Windows.Forms.TabPage();
            this.EffectTab = new System.Windows.Forms.TabPage();
            this.graphicsPanel2 = new Sapphire.GraphicsPanel(this.components);
            this.FramesPerSecond = new System.Windows.Forms.Label();
            this.FramesPerSecondLabel = new System.Windows.Forms.Label();
            this.graphicsPanel1 = new Sapphire.GraphicsPanel(this.components);
            this.SapphireMenu.SuspendLayout();
            this.SapphireControl.SuspendLayout();
            this.RenderTab.SuspendLayout();
            this.RenderSubControl.SuspendLayout();
            this.PostProcessTab.SuspendLayout();
            this.PostProcessEffects.SuspendLayout();
            this.graphicsPanel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // SapphireMenu
            // 
            this.SapphireMenu.BackColor = System.Drawing.Color.DarkSlateGray;
            this.SapphireMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.optionsToolStripMenuItem,
            this.helpToolStripMenuItem});
            this.SapphireMenu.Location = new System.Drawing.Point(0, 0);
            this.SapphireMenu.Name = "SapphireMenu";
            this.SapphireMenu.Size = new System.Drawing.Size(1015, 24);
            this.SapphireMenu.TabIndex = 1;
            this.SapphireMenu.Text = "Menu";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.SapphireFileExit});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // SapphireFileExit
            // 
            this.SapphireFileExit.Name = "SapphireFileExit";
            this.SapphireFileExit.Size = new System.Drawing.Size(92, 22);
            this.SapphireFileExit.Text = "Exit";
            this.SapphireFileExit.Click += new System.EventHandler(this.SapphireFileExit_Click);
            // 
            // optionsToolStripMenuItem
            // 
            this.optionsToolStripMenuItem.Name = "optionsToolStripMenuItem";
            this.optionsToolStripMenuItem.Size = new System.Drawing.Size(61, 20);
            this.optionsToolStripMenuItem.Text = "Options";
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.documentationToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
            this.helpToolStripMenuItem.Text = "Help";
            // 
            // documentationToolStripMenuItem
            // 
            this.documentationToolStripMenuItem.Name = "documentationToolStripMenuItem";
            this.documentationToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
            this.documentationToolStripMenuItem.Text = "Documentation";
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(157, 22);
            this.aboutToolStripMenuItem.Text = "About";
            // 
            // SapphireControl
            // 
            this.SapphireControl.Controls.Add(this.RenderTab);
            this.SapphireControl.Controls.Add(this.LevelTab);
            this.SapphireControl.Controls.Add(this.EffectTab);
            this.SapphireControl.Location = new System.Drawing.Point(659, 37);
            this.SapphireControl.Name = "SapphireControl";
            this.SapphireControl.SelectedIndex = 0;
            this.SapphireControl.Size = new System.Drawing.Size(344, 480);
            this.SapphireControl.TabIndex = 3;
            // 
            // RenderTab
            // 
            this.RenderTab.BackColor = System.Drawing.Color.MediumSlateBlue;
            this.RenderTab.Controls.Add(this.RenderSubControl);
            this.RenderTab.Location = new System.Drawing.Point(4, 22);
            this.RenderTab.Name = "RenderTab";
            this.RenderTab.Padding = new System.Windows.Forms.Padding(3);
            this.RenderTab.Size = new System.Drawing.Size(336, 454);
            this.RenderTab.TabIndex = 0;
            this.RenderTab.Text = "Render";
            // 
            // RenderSubControl
            // 
            this.RenderSubControl.Controls.Add(this.PostProcessTab);
            this.RenderSubControl.Controls.Add(this.tabPage2);
            this.RenderSubControl.Location = new System.Drawing.Point(7, 6);
            this.RenderSubControl.Name = "RenderSubControl";
            this.RenderSubControl.SelectedIndex = 0;
            this.RenderSubControl.Size = new System.Drawing.Size(323, 442);
            this.RenderSubControl.TabIndex = 0;
            // 
            // PostProcessTab
            // 
            this.PostProcessTab.BackColor = System.Drawing.Color.Black;
            this.PostProcessTab.Controls.Add(this.PostProcessEffects);
            this.PostProcessTab.Location = new System.Drawing.Point(4, 22);
            this.PostProcessTab.Name = "PostProcessTab";
            this.PostProcessTab.Padding = new System.Windows.Forms.Padding(3);
            this.PostProcessTab.Size = new System.Drawing.Size(315, 416);
            this.PostProcessTab.TabIndex = 0;
            this.PostProcessTab.Text = "PostProcess";
            // 
            // PostProcessEffects
            // 
            this.PostProcessEffects.Controls.Add(this.PostProcessComboBox);
            this.PostProcessEffects.Controls.Add(this.PostProcessCheckBox);
            this.PostProcessEffects.ForeColor = System.Drawing.Color.MediumSlateBlue;
            this.PostProcessEffects.Location = new System.Drawing.Point(6, 6);
            this.PostProcessEffects.Name = "PostProcessEffects";
            this.PostProcessEffects.Size = new System.Drawing.Size(303, 87);
            this.PostProcessEffects.TabIndex = 1;
            this.PostProcessEffects.TabStop = false;
            this.PostProcessEffects.Text = "Post Process Effects";
            // 
            // PostProcessComboBox
            // 
            this.PostProcessComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.PostProcessComboBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PostProcessComboBox.ForeColor = System.Drawing.Color.MediumSlateBlue;
            this.PostProcessComboBox.FormattingEnabled = true;
            this.PostProcessComboBox.Items.AddRange(new object[] {
            "No Effect",
            "Invert Positions",
            "Invert Colors",
            "MonoChrome",
            "Sepia",
            "Warped",
            "Black and White",
            "Embossed",
            "Color Loop",
            "Tron Energy",
            "Dissolve"});
            this.PostProcessComboBox.Location = new System.Drawing.Point(6, 49);
            this.PostProcessComboBox.Name = "PostProcessComboBox";
            this.PostProcessComboBox.Size = new System.Drawing.Size(291, 28);
            this.PostProcessComboBox.TabIndex = 0;
            this.PostProcessComboBox.SelectedIndexChanged += new System.EventHandler(this.PostProcessComboBox_SelectedIndexChanged);
            // 
            // PostProcessCheckBox
            // 
            this.PostProcessCheckBox.AutoSize = true;
            this.PostProcessCheckBox.Checked = true;
            this.PostProcessCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.PostProcessCheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.PostProcessCheckBox.ForeColor = System.Drawing.Color.MediumSlateBlue;
            this.PostProcessCheckBox.Location = new System.Drawing.Point(6, 19);
            this.PostProcessCheckBox.Name = "PostProcessCheckBox";
            this.PostProcessCheckBox.Size = new System.Drawing.Size(194, 24);
            this.PostProcessCheckBox.TabIndex = 0;
            this.PostProcessCheckBox.Text = "Enable Post Process";
            this.PostProcessCheckBox.UseVisualStyleBackColor = true;
            this.PostProcessCheckBox.CheckedChanged += new System.EventHandler(this.PostProcessCheckBox_CheckedChanged);
            // 
            // tabPage2
            // 
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(315, 416);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // LevelTab
            // 
            this.LevelTab.BackColor = System.Drawing.Color.Black;
            this.LevelTab.Location = new System.Drawing.Point(4, 22);
            this.LevelTab.Name = "LevelTab";
            this.LevelTab.Padding = new System.Windows.Forms.Padding(3);
            this.LevelTab.Size = new System.Drawing.Size(336, 454);
            this.LevelTab.TabIndex = 1;
            this.LevelTab.Text = "Level";
            // 
            // EffectTab
            // 
            this.EffectTab.BackColor = System.Drawing.Color.Black;
            this.EffectTab.Location = new System.Drawing.Point(4, 22);
            this.EffectTab.Name = "EffectTab";
            this.EffectTab.Padding = new System.Windows.Forms.Padding(3);
            this.EffectTab.Size = new System.Drawing.Size(336, 454);
            this.EffectTab.TabIndex = 2;
            this.EffectTab.Text = "Effect";
            // 
            // graphicsPanel2
            // 
            this.graphicsPanel2.BackColor = System.Drawing.Color.DarkSlateGray;
            this.graphicsPanel2.Controls.Add(this.FramesPerSecond);
            this.graphicsPanel2.Controls.Add(this.FramesPerSecondLabel);
            this.graphicsPanel2.Location = new System.Drawing.Point(0, 531);
            this.graphicsPanel2.Name = "graphicsPanel2";
            this.graphicsPanel2.Size = new System.Drawing.Size(1015, 24);
            this.graphicsPanel2.TabIndex = 2;
            // 
            // FramesPerSecond
            // 
            this.FramesPerSecond.AutoSize = true;
            this.FramesPerSecond.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FramesPerSecond.ForeColor = System.Drawing.Color.MediumSpringGreen;
            this.FramesPerSecond.Location = new System.Drawing.Point(60, 2);
            this.FramesPerSecond.Name = "FramesPerSecond";
            this.FramesPerSecond.Size = new System.Drawing.Size(32, 17);
            this.FramesPerSecond.TabIndex = 1;
            this.FramesPerSecond.Text = "----";
            // 
            // FramesPerSecondLabel
            // 
            this.FramesPerSecondLabel.AutoSize = true;
            this.FramesPerSecondLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FramesPerSecondLabel.ForeColor = System.Drawing.Color.DeepSkyBlue;
            this.FramesPerSecondLabel.Location = new System.Drawing.Point(12, 2);
            this.FramesPerSecondLabel.Name = "FramesPerSecondLabel";
            this.FramesPerSecondLabel.Size = new System.Drawing.Size(42, 17);
            this.FramesPerSecondLabel.TabIndex = 0;
            this.FramesPerSecondLabel.Text = "FPS:";
            // 
            // graphicsPanel1
            // 
            this.graphicsPanel1.BackColor = System.Drawing.Color.Black;
            this.graphicsPanel1.Location = new System.Drawing.Point(12, 37);
            this.graphicsPanel1.Name = "graphicsPanel1";
            this.graphicsPanel1.Size = new System.Drawing.Size(640, 480);
            this.graphicsPanel1.TabIndex = 0;
            // 
            // SapphireForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.MidnightBlue;
            this.ClientSize = new System.Drawing.Size(1015, 555);
            this.Controls.Add(this.SapphireControl);
            this.Controls.Add(this.graphicsPanel2);
            this.Controls.Add(this.graphicsPanel1);
            this.Controls.Add(this.SapphireMenu);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.SapphireMenu;
            this.Name = "SapphireForm";
            this.Text = "Sapphire";
            this.SapphireMenu.ResumeLayout(false);
            this.SapphireMenu.PerformLayout();
            this.SapphireControl.ResumeLayout(false);
            this.RenderTab.ResumeLayout(false);
            this.RenderSubControl.ResumeLayout(false);
            this.PostProcessTab.ResumeLayout(false);
            this.PostProcessEffects.ResumeLayout(false);
            this.PostProcessEffects.PerformLayout();
            this.graphicsPanel2.ResumeLayout(false);
            this.graphicsPanel2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public GraphicsPanel graphicsPanel1;
        private System.Windows.Forms.MenuStrip SapphireMenu;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem SapphireFileExit;
        private System.Windows.Forms.ToolStripMenuItem optionsToolStripMenuItem;
        private GraphicsPanel graphicsPanel2;
        private System.Windows.Forms.TabControl SapphireControl;
        private System.Windows.Forms.TabPage RenderTab;
        private System.Windows.Forms.TabPage LevelTab;
        private System.Windows.Forms.TabPage EffectTab;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem documentationToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.Label FramesPerSecondLabel;
        public System.Windows.Forms.Label FramesPerSecond;
        private System.Windows.Forms.TabControl RenderSubControl;
        private System.Windows.Forms.TabPage PostProcessTab;
        private System.Windows.Forms.CheckBox PostProcessCheckBox;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.GroupBox PostProcessEffects;
        public System.Windows.Forms.ComboBox PostProcessComboBox;

    }
}

