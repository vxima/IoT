import numpy as np

class FrameSlottedALOHA:
    def __init__(self, P, N):
        self.P = P
        self.N = N
        self.action_space = range(N)  # start at 0 instead of 1

    def step(self, action):
        if action < 0 or action >= len(self.action_space):
            raise ValueError("Invalid action")

        if np.random.rand() < self.P:
            reward = 1
        else:
            reward = 0

        next_state = np.zeros(self.N)
        next_state[action] = 1

        return next_state, reward


class QLearningAgent:
    def __init__(self, env, alpha, gamma, epsilon):
        self.env = env
        self.alpha = alpha
        self.gamma = gamma
        self.epsilon = epsilon
        self.Q = np.zeros((2 ** env.N, env.N))

    def encode(self, state):
        res = 0
        for i in range(len(state)):
            res += state[i] * (2 ** i)
        return int(res)

    def act(self, state):
        if np.random.rand() < self.epsilon:
            return np.random.choice(self.env.action_space)
        encoded_state = self.encode(state)
        return np.argmax(self.Q[encoded_state])

    def learn(self, state, action, reward, next_state):
        encoded_state = self.encode(state)
        encoded_next_state = self.encode(next_state)
        td_target = reward + self.gamma * np.max(self.Q[encoded_next_state])
        td_error = td_target - self.Q[encoded_state][action]
        self.Q[encoded_state][action] += self.alpha * td_error


if __name__ == '__main__':
    P = 0.5
    N = 10
    num_episodes = 1000
    alpha = 0.1
    gamma = 0.99
    epsilon = 0.1

    env = FrameSlottedALOHA(P, N)
    agent = QLearningAgent(env, alpha, gamma, epsilon)

    num_successes = 0
    for i in range(num_episodes):
        state = np.zeros(N)
        done = False
        while not done:
            action = agent.act(state)
            next_state, reward = env.step(action)
            agent.learn(state, action, reward, next_state)
            state = next_state
            done = True
            if reward == 1:
                num_successes += 1

    print("Success rate: ", num_successes / num_episodes)
    print(agent.Q)
