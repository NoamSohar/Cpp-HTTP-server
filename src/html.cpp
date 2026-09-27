#include "html.hpp"

namespace html {

std::string page(const std::string& title, const std::string& message) {
    return R"(<!doctype html>
<html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>)" + title + R"(</title>
<style>
@import url('https://fonts.googleapis.com/css2?family=Black+Ops+One&family=Space+Mono:wght@400;700&display=swap');
*{box-sizing:border-box}body{margin:0;min-height:100vh;overflow:hidden;color:#fff;background:#080018;font-family:'Space Mono',monospace}
.orb{position:fixed;width:45vmax;height:45vmax;border-radius:50%;filter:blur(30px);opacity:.65;animation:drift 12s ease-in-out infinite alternate}.one{background:#ff00a8;top:-25vmax;left:-16vmax}.two{background:#00e5ff;bottom:-28vmax;right:-18vmax;animation-delay:-5s}.three{background:#8bff00;top:35%;left:36%;width:20vmax;height:20vmax;animation-delay:-9s}
.grid{position:fixed;inset:0;background:linear-gradient(#ffffff16 1px,transparent 1px),linear-gradient(90deg,#ffffff16 1px,transparent 1px);background-size:48px 48px;transform:perspective(350px) rotateX(58deg) scale(1.8);transform-origin:bottom;opacity:.4}
main{position:relative;z-index:1;min-height:100vh;display:grid;place-items:center;padding:30px;text-align:center}.panel{max-width:900px;padding:clamp(28px,6vw,72px);border:2px solid #fff;border-radius:28px;background:#0a0716a8;box-shadow:0 0 0 8px #ff00a8,0 0 0 16px #00e5ff,0 25px 80px #000;backdrop-filter:blur(16px);transform:rotate(-1.5deg)}
.eyebrow{display:inline-block;padding:8px 14px;border:2px solid #caff00;border-radius:999px;color:#caff00;background:#000;font-size:12px;letter-spacing:2px;animation:pulse 1s steps(2) infinite}h1{margin:22px 0 12px;font:clamp(3.7rem,11vw,8.5rem)/.82 'Black Ops One',impact,sans-serif;letter-spacing:-3px;text-transform:uppercase;text-shadow:5px 5px #ff00a8,-5px -5px #00e5ff;animation:tilt 2.5s ease-in-out infinite alternate}p{max-width:600px;margin:20px auto;font-size:clamp(.9rem,2vw,1.15rem);line-height:1.8;color:#f4f0ff}
.stats{display:flex;justify-content:center;gap:12px;flex-wrap:wrap;margin:32px 0}.stat{padding:14px 18px;border:1px solid #fff;border-radius:10px;background:#0008;text-align:left}.stat b{display:block;color:#caff00;font-size:1.35rem}.stat span{font-size:10px;letter-spacing:1px}.button{border:0;border-radius:999px;padding:17px 28px;background:#caff00;color:#080018;font:700 15px 'Space Mono',monospace;cursor:pointer;box-shadow:0 7px #6c8500;transition:.15s}.button:hover{transform:translateY(-3px) scale(1.04)}.button:active{transform:translateY(5px);box-shadow:0 2px #6c8500}.corner{position:fixed;z-index:2;font-size:11px;color:#caff00;letter-spacing:1px}.tl{top:18px;left:18px}.br{right:18px;bottom:18px}.confetti{position:fixed;z-index:3;width:10px;height:18px;top:-25px;animation:fall linear infinite}
@keyframes drift{to{transform:translate(18vmax,12vmax) scale(1.25)}}@keyframes pulse{50%{filter:brightness(2);transform:scale(1.08)}}@keyframes tilt{to{transform:rotate(1deg) scale(1.015)}}@keyframes fall{to{transform:translateY(110vh) rotate(720deg)}}
</style></head><body><div class="orb one"></div><div class="orb two"></div><div class="orb three"></div><div class="grid"></div><div class="corner tl">◉ HTTP/1.1 // ONLINE</div><div class="corner br">PORT 8080 // ACTIVE</div><main><section class="panel"><span class="eyebrow">✦ SYSTEM STATUS: UNREASONABLY SUCCESSFUL ✦</span><h1>It<br>Worked!</h1><p>It worked. welcome to this vibe coded ah website</p><div class="stats"><div class="stat"><b>200</b><span>STATUS CODE</span></div><div class="stat"><b>∞</b><span>UPTIME</span></div><div class="stat"><b>8080</b><span>PORT POWER</span></div></div><button class="button" onclick="this.textContent='CONFIRMED: STILL WORKING ✦'">PRESS FOR VALIDATION</button></section></main><script>for(let i=0;i<80;i++){const c=document.createElement('i');c.className='confetti';c.style.left=Math.random()*100+'vw';c.style.background=['#ff00a8','#00e5ff','#caff00','#ffd000','#fff'][i%5];c.style.animationDuration=3+Math.random()*5+'s';c.style.animationDelay=-Math.random()*7+'s';document.body.append(c)}</script></body></html>)";
}

}  // namespace html
