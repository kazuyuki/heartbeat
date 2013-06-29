heartbeat
=========

NP解決可能な最小のクラスタは 3ノードで構成される。

http://node1/heartbeat/ にアクセスすると、node1 の持つ vector clock が取得できる。

	$> curl http://node1/heartbeat
	node1, t1
	node2, t2
	node3, t3

上記では、クラスタは node1, node2, node3 からなり、node1が認識する各ノードの時刻は t1, t2, t3 である。
