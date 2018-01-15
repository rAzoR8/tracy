
#[string]$SolutionDir = "C:\Projects\Tracy\Source\"
[string]$SolutionDir = "..\"
[string]$BoostBinReleaseDir = ($SolutionDir + "boost\bin\release\")
[string]$BoostBinDebugDir = ($SolutionDir + "boost\bin\debug\")
[string]$BoostInputFiles = ($SolutionDir + "boost\bin.v2\libs\")

if (!(Test-Path -path $BoostBinReleaseDir))
{
    New-Item $BoostBinReleaseDir -Type Directory
}

if (!(Test-Path -path $BoostBinDebugDir))
{
    New-Item $BoostBinDebugDir -Type Directory
}

foreach ($file in get-ChildItem -recurse -path $BoostInputFiles -include *.lib)
{
    if($file.Name.Contains("x64"))
    {
        Echo ("Copying " + $file.Name)
        if($file.FullName.Contains("debug"))
        {        
           Move-Item $file $BoostBinDebugDir
        }
        if($file.FullName.Contains("release"))
        {
           Move-Item $file $BoostBinReleaseDir    
        }
    }
}