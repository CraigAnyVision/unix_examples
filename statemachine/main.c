#include <stdio.h>
#include <unistd.h>

enum state_codes
{
	start, foo, bar, end
};

enum ret_codes
{
	ok, fail, repeat
};

int start_state(void)
{
	printf("Entry\n");
	sleep(2);
	return ok;
}

int foo_state(void)
{
	static int i = 3;
	printf("Foo %d\n", i);
	sleep(2);
	if (--i > 0)
	{
		return repeat;
	}
	else return ok;
}

int bar_state(void)
{
	printf("Bar\n");
	sleep(2);
	return end;
}

int exit_state(void)
{
	printf("Exit\n");
	sleep(2);
	return ok;
}

// array and enum below must be in sync!
int (*state[])(void) = {start_state, foo_state, bar_state, exit_state};

struct transition
{
	enum state_codes src_state;
	enum ret_codes ret_code;
	enum state_codes dst_state;
};

// transitions from end state aren't needed
struct transition state_transitions[] = {
		{start, ok,     foo},
		{start, fail,   end},
		{foo,   ok,     bar},
		{foo,   fail,   end},
		{foo,   repeat, foo},
		{bar,   ok,     end},
		{bar,   fail,   end},
		{bar,   repeat, foo}};

static enum state_codes lookup_transitions(int current_state, int input)
{
	enum state_codes temp = end;

	for (int i = 0; i < 8 ; i++)
	{
		if (state_transitions[i].src_state == current_state && state_transitions[i].ret_code == input)
		{
			temp = state_transitions[i].dst_state;
			break;
		}
	}
	return temp;
}

int main(int argc, char *argv[])
{
	enum state_codes cur_state = start;
	int rc;
	int (*state_fun)(void);

	for (;;)
	{
		state_fun = state[cur_state];
		rc = state_fun();
		if (end == cur_state)
		{
			break;
		}
		cur_state = lookup_transitions(cur_state, rc);
	}

	return 0;
}
