static int
shifttag(int dist)
{
	int i, curtags;
	int seltag = 0;
	int numtags = LENGTH(tags);

	curtags = selmon->tagset[selmon->seltags];
	for(i = 0; i < LENGTH(tags); i++) {
		if((curtags & (1 << i)) != 0) {
			seltag = i;
			break;
		}
	}

	seltag += dist;
	if(seltag < 0)
		seltag = numtags - (-seltag) % numtags;
	else
		seltag %= numtags;

	return 1 << seltag;
}

static void
cycle(const Arg *arg)
{
	const Arg a = { .i = shifttag(arg->i) };
	view(&a);
}

static void
tagcycle(const Arg *arg)
{
	const Arg a = { .i = shifttag(arg->i) };
	tag(&a);
	view(&a);
}
