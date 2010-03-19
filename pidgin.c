static const char wmname[] = "Buddy List";

static void
pidgin(Monitor *m) {
	int x, y, h, w, ww;
	unsigned int i, n;
	Client *c, *mk = 0;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++)
		if(strstr(c->name, wmname))
			mk = c;
	if(n == 0)
		return;
	/* master */
	ww = m->mfacts[m->curtag] * m->ww;
	if(mk) {
		resize(mk, m->wx + ww, m->wy, m->ww - ww - 2 * mk->bw, m->wh - 2 * mk->bw, False);
		strncpy(m->ltsymbol, "==P", sizeof m->ltsymbol);
		if(--n == 0)
			return;
	}
	/* tile stack */
	x = m->wx;
	y = m->wy;
	w = mk ? ww : m->ww;
	h = m->wh / n;
	if(h < bh)
		h = m->wh;
	for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if(c == mk) {
			--i;
			continue;
		}
		resize(c, x, y, w - 2 * c->bw,
		       ((i + 1 == n) ? m->wy + m->wh - y : h) - 2 * c->bw, False);
		if(h != m->wh)
			y = c->y + HEIGHT(c);
	}
}
