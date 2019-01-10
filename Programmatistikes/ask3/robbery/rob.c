#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct edge {
	int a, b, c;
	int out, checked;
};

struct node {
	int parent, rank;
};

struct vertex {
	int num, index;
	struct vertex *next;
};

static struct vertex *adj[50000];
static struct edge graph[500000];
static struct node nodes[50000];
int all = 0, none = 0, some = 0, t;
int p[50000];
int d[50000];
int l[50000];
int m[50000];
int b[500000];
int dup[500000];

void dfs(int u)
{
	struct vertex *ptr;
	int v;

	l[u] = d[u] = ++t;
	ptr = adj[u];
	m[u] = 1;
	while (ptr != NULL) {
		v = ptr->num;
		if (!m[v]) {
			p[v] = u;
			dfs(v);
			l[u] = MIN(l[u], l[v]);
			if (l[v] > d[u] && !dup[ptr->index])
				b[ptr->index] = 1;
		} else if (v != p[u]) {
			l[u] = MIN(l[u], d[v]);
		}
		ptr = ptr->next;
	}
}

int contains(struct vertex *ptr, int x)
{
	while (ptr != NULL) {
		if (ptr->num == x) {
			dup[ptr->index] = 1;
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}


int find(int x)
{
	if (nodes[x].parent != x)
		nodes[x].parent = find(nodes[x].parent);

	return nodes[x].parent;
}

int comp(const void *a, const void *b)
{
	const struct edge *a1 = a;
	const struct edge *b1 = b;

	return (a1->c - b1->c);
}

int main(void)
{
	int N, M, x, y, weight;
	int cnt, i, j, k;
	struct edge temp;
	struct vertex *ptr, *tmp;

	scanf("%d",&N);
	scanf("%d",&M);

	for (i = 0; i < M; i++) {
		scanf("%d",&temp);
		graph[i].a=temp-1;
		scanf("%d",&temp);
		graph[i].b = temp-1;
		scanf("%d",&temp);
		graph[i].c = temp;
		graph[i].out = graph[i].checked = 0;
	}

	qsort(graph, M, sizeof(struct edge), comp);

	for (i = 0; i < N; i++) {
		nodes[i].parent = i;
		nodes[i].rank = 0;
		adj[i] = NULL;
	}

	memset(dup, 0, sizeof(dup));
	memset(b, 0, sizeof(b));
	cnt = 0;
	i = 0;
	while (i < M) {
		weight = graph[i].c;
		j = i;
		do {
			x = find(graph[j].a);
			y = find(graph[j].b);
			if (x == y) {
				none++;
				graph[j].out = 1;
			}
		} while (j < M && graph[++j].c == weight);

		for (k = i; k < j; k++) {
			if (!graph[k].out) {
				x = find(graph[k].a);
				y = find(graph[k].b);
				if (!contains(adj[x], y)) {
					ptr = malloc(sizeof(*ptr));
					ptr->num = y;
					ptr->next = adj[x];
					adj[x] = ptr;
					ptr->index = k;
					ptr = malloc(sizeof(*ptr));
					ptr->num = x;
					ptr->next = adj[y];
					adj[y] = ptr;
					ptr->index = k;
				} else {
					dup[k] = 1;
				}
			}
		}

		t = 0;
		memset(p, 0, sizeof(p));
		memset(d, 0, sizeof(d));
		memset(l, 0, sizeof(l));
		memset(m, 0, sizeof(m));
		for (k = 0; k < N; k++)
			if (!m[k] && adj[k] != NULL)
				dfs(k);

		for (k = 0; k < N; k++) {
			ptr = adj[k];
			adj[k] = NULL;
			while (ptr != NULL) {
				tmp = ptr;
				ptr = ptr->next;
				free(tmp);
			}
		}

		for (; i < j; i++) {
			if (b[i])
				all++;
			x = find(graph[i].a);
			y = find(graph[i].b);
			if (x == y)
				continue;
			if (nodes[x].rank < nodes[y].rank) {
				nodes[x].parent = y;
			} else if (nodes[x].rank > nodes[y].rank) {
				nodes[y].parent = x;
			} else {
				nodes[y].parent = x;
				nodes[x].rank++;
			}
			cnt++;
		}
	}

	some = M - all - none;
	printf("%d\n%d\n%d\n", all, none, some);

	return 0;
}
