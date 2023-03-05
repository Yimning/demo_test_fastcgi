<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-redpacket_fill"></i> js调用摄像头拍照保存图片 </el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <div align="center">
                <p id="flag" class="tishi"></p>
            </div>

            <el-button type="primary" icon="el-icon-camera-solid" @click="openCamera" :src="headImgSrc">打开摄像头</el-button>
            <el-button type="danger" icon="el-icon-camera-solid" @click="closeCamera" v-bind:disabled="!openIsCheck">关闭摄像头</el-button>
            <!--图片展示-->
            <!--确认-->
            <el-button type="info" icon="el-icon-camera-solid" @click="photograph" v-bind:disabled="!openIsCheck">拍照</el-button>

            <div>
                <!--开启摄像头-->
                <!-- <img @click="openCamera" :src="headImgSrc" alt="摄像头" /> -->
                <video ref="video" width="480px" height="400px" autoplay="autoplay"></video>

                <!--canvas截取流-->
                <canvas ref="canvas" width="480px" height="400px" style="display: none"></canvas>
            </div>
            <!-- <el-button plain @click="open2"> 警告 </el-button> -->
        </div>
    </div>
</template>

<script>
export default {
    data() {
        return {
            headImgSrc: '',
            flag: false,
            openIsCheck: false,
            roseID: this.$store.getters.getUser.roseID,
            userID: this.$store.getters.getUser.userID
        };
    },
    methods: {
        // 调用摄像头
        openCamera() {
            // H5调用电脑摄像头API
            navigator.mediaDevices
                .getUserMedia({
                    video: true
                })
                .then((success) => {
                    // 摄像头开启成功
                    this.$refs['video'].srcObject = success;
                    this.openIsCheck = true;

                    // 实时拍照效果
                    this.$refs['video'].play();
                })
                .catch((error) => {
                    console.error('摄像头开启失败，请检查摄像头是否可用！');
                });
            setTimeout(() => {
                //设置延迟执行
                this.photograph();
                this.$refs['video'].load();
                //  console.log('---------------------');
            }, 5000);
            this.$refs['video'].load();
        },
        test() {
            console.log(this.$refs.video);
        },
        // 拍照
        photograph() {
            let ctx = this.$refs['canvas'].getContext('2d');
            // 把当前视频帧内容渲染到canvas上
            ctx.drawImage(this.$refs['video'], 0, 0, 640, 480);
            // 转base64格式、图片格式转换、图片质量压缩
            let imgBase64 = this.$refs['canvas'].toDataURL('image/jpeg', 0.7); // 由字节转换为KB 判断大小

            let str = imgBase64.replace('data:image/jpeg;base64,', '');
            //console.log(str);//去除data:image/jpeg;base64,
            let strLength = str.length;
            let fileLength = parseInt(strLength - (strLength / 8) * 2); // 图片尺寸  用于判断
            let size = (fileLength / 1024).toFixed(2);
            //console.log(size); // 上传拍照信息  调用接口上传图片 .........

            // 保存到本地
            let ADOM = document.createElement('a');
            this.open2();
            ADOM.href = imgBase64;
            if (this.roseID === '0') {
                ADOM.download = this.userID + '.jpeg';
            } else if (this.roseID === '1') {
                ADOM.download = this.userID + '.jpeg';
            } else {
                ADOM.download = new Date().getTime() + '.jpeg';
            }
            ADOM.click();
        },     
        // 关闭摄像头 
        closeCamera() {
            if (!this.$refs['video'].srcObject) return;
            let stream = this.$refs['video'].srcObject;
            let tracks = stream.getTracks();
            tracks.forEach((track) => {
                track.stop();
                this.openIsCheck = false;
            });
            this.$refs['video'].srcObject = null;
        },
        open2() {
            this.$notify({
                title: '提示',
                message: '请严格使用用户账号命名',
                type: 'warning'
            });
        }
    }
};
</script>

<style>
.getface {
    position: absolute;
    top: 20%;
    left: 35%;
    box-shadow: 0 0px 12px 0 rgba(0, 0, 0, 0.1);
}
.tishi {
    font-size: 20px;
}
</style>



