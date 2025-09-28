

类似于redis的实现，自定义协议，比如
//获取锁
@LOCK ACQ mykey 1000
//续期锁
@LOCK REN mykey 500
//释放锁
@LOCK REL mykey
