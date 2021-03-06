#include <winsock2.h> 
#include <windef.h>
#include <iostream> 
#include <vector>
#pragma comment(lib,"ws2_32")

using namespace std;
typedef unsigned int uint;
vector<uint> v;

main() 
{ 
 WORD wsVersion = MAKEWORD(2,0); 
 WSADATA wsaData; 
 struct sockaddr_in sin;   //sockaddr_in结构,表示socket address and internet style
 uint BeginPort;     //开始端口 
 uint EndPort;     //结束端口 
 uint CurrentPort;    //正在扫描的端口 
 uint i=0;

 char HostName[256];    //要扫描的主机 
 SOCKET s;
 int OpenPort;     //开放端口个数 
 OpenPort = 0;


 cout<<"Please input the HostName:";
 cin>>HostName;
 cout<<"Input the Begin Port:";
 cin>>BeginPort;
 cout<<"Input the End port:";
 cin>>EndPort;

 //对输入的端口判断 
 while((BeginPort > EndPort || BeginPort < 0 || BeginPort >65535 || EndPort <0 || EndPort >65535))
 { 
	  cout<<"You have input some wrong paramters.Try again."<<endl;
	  cout<<"Please input the HostName:";
	  cin>>HostName;
	  cout<<"Input the Begin Port:";
	  cin>>BeginPort;
	  cout<<"Input the End port:";
	  cin>>EndPort;
 }

 if(WSAStartup(wsVersion,&wsaData)) 
 { 
	cout<<"Initial Failed!"<<endl;  return -1;
 } 
 cout<<endl<<"Now Scan "<<HostName<<"'s Specified Ports Status."<<endl<<endl;

 //判断端口是否开放并记录
 for(CurrentPort=BeginPort; CurrentPort<=EndPort;++CurrentPort) 
 { 
    s = socket(AF_INET,SOCK_STREAM,0); //s用来记录socket的返回值。
    if(s == INVALID_SOCKET) 
    { 
   cout<<"Establish Socket Failed."<<endl;  WSACleanup();   
    } 
    sin.sin_family = AF_INET;
    sin.sin_port = htons(CurrentPort); //当前扫描的端口号
    sin.sin_addr.S_un.S_addr = inet_addr(HostName);

    if(connect(s,(struct sockaddr*)&sin,sizeof(sin)) == SOCKET_ERROR) 
    { 
		 cout<<"Port: "<<CurrentPort<<", Status: Not open."<<endl;
		 closesocket(s);//连接失败
    } 
    else 
    { 
		 cout<<"Port: "<<CurrentPort<<", Status: Opened."<<endl;
		 OpenPort ++;  
		 v.push_back(CurrentPort);
		 closesocket(s); 
    }   
  }

  cout<<endl<<"Resaults: Host "<<HostName<<" has opened "<<OpenPort<<" port.Opened port as follow:"<<endl; 
 cout<<"================================"<<endl;
  for(i=0;i<v.size();++i)
  {
  cout<<v.at(i)<<" ";
  if((i+1)%10==0)cout<<endl;
  }
  cout<<endl;
  cout<<"=============================="<<endl;
  closesocket(s);
     WSACleanup();

  return 0; 
}

