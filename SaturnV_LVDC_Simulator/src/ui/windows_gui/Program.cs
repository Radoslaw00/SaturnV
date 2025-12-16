using System;
using System.Diagnostics;
using System.IO;

class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Starting LVDC Dashboard...");
        
        string exePath = Path.Combine(Directory.GetCurrentDirectory(), "build", "LVDC_Simulator.exe");
        if (!File.Exists(exePath)) {
             // Fallback if running from bin/Debug
             exePath = Path.Combine(Directory.GetCurrentDirectory(), "..", "..", "..", "build", "LVDC_Simulator.exe");
        }
        exePath = Path.GetFullPath(exePath);

        if (!File.Exists(exePath))
        {
            Console.WriteLine($"Error: Simulator executable not found at {exePath}");
            Console.WriteLine("Please run scripts/compile_all.bat first.");
            return;
        }

        ProcessStartInfo startInfo = new ProcessStartInfo();
        startInfo.FileName = exePath;
        startInfo.RedirectStandardOutput = true;
        startInfo.UseShellExecute = false;
        startInfo.CreateNoWindow = true;

        Process process = new Process();
        process.StartInfo = startInfo;
        process.OutputDataReceived += (sender, e) => 
        {
            if (!String.IsNullOrEmpty(e.Data))
            {
                if (e.Data.StartsWith("TLM:"))
                {
                    ParseTelemetry(e.Data);
                }
                else
                {
                    Console.WriteLine($"[SIM]: {e.Data}");
                }
            }
        };

        process.Start();
        process.BeginOutputReadLine();
        process.WaitForExit();
    }

    static void ParseTelemetry(string line)
    {
        // TLM:tick|A|Q|IA
        try {
            string data = line.Substring(4);
            string[] parts = data.Split('|');
            Console.ForegroundColor = ConsoleColor.Green;
            Console.Write($"\rTICK: {parts[0]} | A: {parts[1]} | Q: {parts[2]} | IA: {parts[3]}     ");
            Console.ResetColor();
        } catch { }
    }
}
