package networks

import(
	"net"
	"testing"
)

func listen(t *testing.T)
{
	listener, stderr := net.Listen("tcp","127.0.0.1:0")
	if err!=nil {t.Fatal(err)}
	defer func() {_ = listener.Close()}()
	t.Logf("bound to %q", listener.Addr())
}