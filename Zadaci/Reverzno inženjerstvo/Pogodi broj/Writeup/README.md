<img width="663" height="555" alt="slika" src="https://github.com/user-attachments/assets/7ac2b884-aadf-49ad-8de2-d857d1a8603d" />


```

int __cdecl main(int _Argc,char **_Argv,char **_Env)

{
  ostream *poVar1;
  double dVar2;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  __main();
  local_c = 0x14e4;
  local_10 = 0xcc0;
  dVar2 = (double)std::pow<int,int>(0xcc0,0);
  local_14 = (int)dVar2;
  std::operator<<((ostream *)&_ZSt4cout,"Pogodi broj: ");
  std::istream::operator>>((istream *)&_ZSt3cin,&local_18);
  if (local_c * local_10 * local_14 == local_18) {
    poVar1 = std::operator<<((ostream *)&_ZSt4cout,"Tocan broj!");
    std::ostream::operator<<(poVar1,std::endl<>);
  }
  else {
    poVar1 = std::operator<<((ostream *)&_ZSt4cout,"Pogresan broj, pokusaj ponovo!");
    std::ostream::operator<<(poVar1,std::endl<>);
  }
  system("pause");
  return 0;
}


```
