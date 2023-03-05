<template>
    <div>
        <div class="crumbs">
            <el-breadcrumb separator="/">
                <el-breadcrumb-item> <i class="el-icon-lx-calendar"></i>人脸库管理 </el-breadcrumb-item>
                <el-breadcrumb-item>更新人脸</el-breadcrumb-item>
            </el-breadcrumb>
        </div>
        <div class="container">
            <div class="el-upload__tip" slot="tip">只能上传jpg、jpeg/png文件，且不超过500kb</div>
            <div class="content-title">支持裁剪</div>
            <div class="plugins-tips">
                注意:图片名严格以学号命名，例如：1234.jpeg;教师与管理员严格以账号命名,例如：T001/A001.jpeg
                <!-- vue-cropperjs：一个封装了 cropperjs 的 Vue 组件。
                访问地址：-->
                <!-- <a href="https://github.com/Agontuk/vue-cropperjs" target="_blank">vue-cropperjs</a> -->
            </div> 
            <div class="crop-demo">
                <img :src="cropImg" class="pre-img" />

                <div class="crop-demo-btn">
                    选择图片
                    <input class="crop-input" type="file" name="image" accept="image/*" @change="setImage" />
                </div>
                <div v-if="showFlag">
                    <el-button style="margin-left: 30px" size="small" type="success" @click="submitUpload">上传更新</el-button>
                </div>
            </div>

            <el-dialog title="裁剪图片" :visible.sync="dialogVisible" width="30%">
                <vue-cropper
                    ref="cropper"
                    :src="imgSrc"
                    :ready="cropImage"
                    :zoom="cropImage"
                    :cropmove="cropImage"
                    style="width: 100%; height: 300px"
                ></vue-cropper>
                <span slot="footer" class="dialog-footer">
                    <el-button @click="cancelCrop">取 消</el-button>
                    <el-button type="primary" @click="dialogVisible = false">确 定</el-button>
                </span>
            </el-dialog>
        </div>
    </div>
</template>

<script>
import VueCropper from 'vue-cropperjs';

export default {
    name: 'updateFace.vue',
    inject: ['reload'],
    data() {
        return {
            defaultSrc: require('../../assets/image/avatar.jpg'),
            fileList: [],
            imgSrc: '',
            cropImg: '',
            dialogVisible: false,
            showFlag: false,
            strName: '',
            ruleForm: {
                imgpath: '',
                userID: ''
            }
        };
    },
    components: {
        VueCropper
    },
    methods: {
        setImage(e) {
            const file = e.target.files[0];
            if (!file.type.includes('image/')) {
                return;
            }
            const fileName = e.target.files[0].name;
            const strSplit = fileName.split('.');
            // console.log(fileName);
            // console.log(strSplit);
            // console.log(strSplit[0]);
            this.strName = strSplit[0];

            const reader = new FileReader();
            reader.onload = (event) => {
                this.dialogVisible = true;
                this.imgSrc = event.target.result;
                this.$refs.cropper && this.$refs.cropper.replace(event.target.result);
                this.showFlag = true;
                //console.log(this.imgSrc);
                this.ruleForm.imgpath = this.imgSrc;
                this.ruleForm.userID = this.strName;
            };
            reader.readAsDataURL(file); // 请求图片数据
            // console.log(reader);
        },
        submitAxious() {
            const that = this;
            this.$axios
                .post('/api/updateFace', this.ruleForm)
                .then((res) => {
                    console.log(res);
                    // error_code: 222202
                    if (res.data.error_code === 0) {
                        this.$message.success(`更新成功`);
                        that.cropImg = that.defaultSrc;
                    }
                    if (res.data.error_code === 222202) {
                        this.$message.error(`图片不存在人脸,请真实上传人脸`);
                        that.cropImg = that.defaultSrc;
                    }
                    if (res.data.error_code === 222203) {
                        this.$message.error(`已存在存在人脸,无需重新上传`);
                        that.cropImg = that.defaultSrc;
                    }
                    if (res.data.error_code === 223103) {
                        this.$message.error(`不存在人脸,请上传`);
                        that.cropImg = that.defaultSrc;
                    }
                    if (res.data === '') {
                        this.$message.error(`更新失败,上传时请确认网络连接正常`);
                        that.cropImg = that.defaultSrc;
                    }
                })
                .catch((err) => {
                    //  console.log(err);
                    if (err.response.status === 400) {
                        this.$message.error(`请求错误`);
                    }
                    if (err.response.status === 500) {
                        this.$message.error(`请求失败，请选择图片`);
                    }
                });
            this.reload(); //刷新 ----推荐
        },
        submitUpload() {
            const that = this;
            const BASE64 = this.ruleForm.imgpath.split(',');
            this.ruleForm.imgpath = BASE64[1];
            //console.log(this.ruleForm.imgpath);
            //限制管理员角色权限，否则其他用户修改他人的信息
            if (this.$store.getters.getUser.roseID === '2') {
                this.submitAxious();
            } else {
                if (this.ruleForm.userID == this.$store.getters.getUser.userID) {
                    this.submitAxious();
                } else {
                    this.$message.error(`当前账号与图片命名不一致`);
                }
            }
        },
        cropImage() {
            this.cropImg = this.$refs.cropper.getCroppedCanvas().toDataURL();
        },
        cancelCrop() {
            this.dialogVisible = false;
            this.cropImg = this.defaultSrc;
        },
        imageuploaded(res) {
            //console.log(res);
        },
        handleError() {
            this.$notify.error({
                title: '上传失败',
                message: '图片上传接口上传失败,服务器接口无响应'
            });
        }
    },
    created() {
        this.cropImg = this.defaultSrc;
    }
};
</script>

<style scoped>
.content-title {
    font-weight: 400;
    line-height: 50px;
    margin: 10px 0;
    font-size: 22px;
    color: #1f2f3d;
}
.pre-img {
    width: 100px;
    height: 100px;
    background: #f8f8f8;
    border: 1px solid #eee;
    border-radius: 5px;
}
.crop-demo {
    display: flex;
    align-items: flex-end;
}
.crop-demo-btn {
    position: relative;
    width: 100px;
    height: 32px;
    line-height: 32px;
    padding: 0 20px;
    margin-left: 30px;
    background-color: #409eff;
    color: #fff;
    font-size: 12px;
    border-radius: 4px;
    box-sizing: border-box;
}
.crop-input {
    position: absolute;
    width: 100px;
    height: 32px;
    left: 0;
    top: 0;
    opacity: 0;
    cursor: pointer;
}
</style>