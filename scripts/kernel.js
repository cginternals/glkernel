var kernel = new Kernel2(10, 5, 2);

kernel.sequence.uniform(0.0, 1.0);
kernel.shuffle.random();
kernel.scale.range(-1,1);
kernel.sort.distance(0);

kernel.kernel
