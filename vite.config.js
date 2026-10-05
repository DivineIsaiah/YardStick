import { defineConfig } from 'vite';

export default defineConfig(({ command }) => ({
  appType: 'mpa',
  base: command === 'build' ? '/YardStick/' : '/',
  build: {
    rollupOptions: {
      input: {
        main: 'index.html',
        calculator: 'calculator.html',
        history: 'history.html'
      }
    }
  }
}));