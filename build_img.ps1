$f = [System.IO.File]::OpenWrite('ketos.img');


$f.Position = 0;
$b = [System.IO.File]::ReadAllBytes('bootloader.bin');
$f.Write($b, 0, $b.Length);


$f.Position = 512;
$b = [System.IO.File]::ReadAllBytes('stage2.bin');
$f.Write($b, 0, $b.Length);


$f.Position = 1024;
$b = [System.IO.File]::ReadAllBytes('ketoskrnl.bin');
$f.Write($b, 0, $b.Length);


$f.SetLength(131072)
$f.Close();