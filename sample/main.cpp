#include <locale>
#include <iUserMonitorSDK.h>
#include <iUserMonitorProtocol.h>

class UserMontorCallback : public IUserMonitorCallback
{
public:
	void OnCallback(IUserMonitorMessage* msg)
	{
		printf("%S ==> %S\n", msg->GetTypeName(), msg->GetFormatedString(emMSGFieldCurrentProcessPath));
		printf("\t%30S : %-30d\n", _T("ProcessType"), msg->GetHeader()->CurrentProcessType);

		for (ULONG i = emMSGFieldPath; i < msg->GetFieldCount(); i++) {
			printf("\t%30S : %-30S\n", msg->GetFieldName(i), msg->GetFormatedString(i));
		}
	}
};

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs");

	UserMonitorManager mgr;
	UserMontorCallback callback;

	HRESULT hr = mgr.Start(&callback);

	if (hr != S_OK) {
		printf("start error = %08X", hr);
		return -1;
	}

	printf("启动成功\n");
	printf("iUserMonitor内部会遍历进程尝试注入到需要Hook的进程，如果出现安全软件拦截提示，请放行。\n");
	printf("如果需要更好的注入方式，先配合使用iMonitor的内核级注入方式。\n");
	printf("为了稳定，退出后不会卸载已经注入的模块，如果需要删除，请先重启被注入的软件或者系统。\n");
	printf("\n");

	WaitForSingleObject(GetCurrentThread(), INFINITE);

	return 0;
}
